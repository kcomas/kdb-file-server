
#include "./file_server.h"

static int file_members_count = 0;

static struct FileMember** File_Server_File_Members;

static char* file_server_directory = NULL;

const static int file_server_mime_members_length = 2;

const static struct MimeType File_Server_Mime_Types[] = {
    {"html", "text/html"},
    {"js", "application/javascript"},
    {"text", "text/plain"}
};

const static int file_server_status_messages_length = 3;

const static struct StatusCodeMessage File_Server_Status_Messages[] = {
    {200, " OK"},
    {404, " Not Found"},
    {500, " Internal Server Error"}
};

void file_server_set_directory(const char* folder) {

    if (file_server_directory != NULL) {
        free(file_server_directory);
    }

    file_server_directory = (char*) malloc(strlen(folder) + 1);

    if (!file_server_directory) {
        fprintf(stderr, "ERROR: Unable to malloc main directory");
        return;
    }

    strcpy(file_server_directory, folder);
}

char* file_server_quick_copy(const char* str) {
    char* str2 = (char*) malloc(strlen(str) + 1);
    strcpy(str2, str);
    return str2;
}

char* file_server_join_path(const char* path) {
    if (file_server_directory == NULL) {
        fprintf(stderr, "ERROR: file_server_directory not set\n");
        return file_server_quick_copy(path);
    }

    char* joined = (char*) malloc(strlen(file_server_directory) + strlen(path) + 1);

    if (!joined) {
        fprintf(stderr, "ERROR: Unable to malloc join");
        return file_server_quick_copy(path);
    }

    strcpy(joined, file_server_directory);
    strcat(joined, path);
    return joined;
}

const char* file_server_determine_mime(const char* filename) {
    const char* dot = strrchr(filename, '.');
    if (!dot || dot == filename) {
        return "application/octet-stream";
    }

    const char* ext = dot + 1;

    for (int i = 0; i < file_server_mime_members_length; i++) {
        if (strcmp(File_Server_Mime_Types[i].ext, ext) == 0) {
            return File_Server_Mime_Types[i].mime;
        }
    }

    return "application/octet-stream";
}

const char* file_server_determine_status_name(int status) {
    for (int i = 0; i < file_server_status_messages_length; i++) {
        if (File_Server_Status_Messages[i].code == status) {
            return File_Server_Status_Messages[i].message;
        }
    }

    return "";
}

char* file_server_build_response(const int status_code, const char* mime, const char* body) {

    const char* new_line = "\r\n";
    const size_t new_line_length = strlen(new_line);

    const char* double_new_line = "\r\n\r\n";
    const size_t double_new_line_length = strlen(double_new_line);

    const char* http_version = "HTTP/1.1 ";
    char http_version_code[4];
    snprintf(http_version_code, 4, "%i", status_code);
    const char* http_status_code_name = file_server_determine_status_name(status_code);

    size_t http_version_length = strlen(http_version) + 3 + new_line_length + strlen(http_status_code_name);
    char* http_version_line = (char*) malloc(http_version_length);
    strcpy(http_version_line, http_version);
    strcat(http_version_line, http_version_code);
    strcat(http_version_line, http_status_code_name);
    strcat(http_version_line, new_line);

    const char* content_type = "Content-Type: ";

    size_t content_type_length = strlen(content_type) + strlen(mime) + new_line_length;
    char* content_type_line = (char*) malloc(content_type_length);
    strcpy(content_type_line, content_type);
    strcat(content_type_line, mime);
    strcat(content_type_line, new_line);

    size_t response_length = http_version_length + content_type_length + double_new_line_length + strlen(body);
    char* response = (char*) malloc(response_length);
    strcpy(response, http_version_line);
    free(http_version_line);

    strcat(response, content_type_line);
    free(content_type_line);

    strcat(response, double_new_line);
    strcat(response, body);

    return response;
}

char* file_server_load_file(const char* filename) {

    FILE* f;
    long file_size;
    char* file_data;

    char* fullname = file_server_join_path(filename);

    f = fopen(fullname, "rb");

    free(fullname);

    if (!f) {
        return file_server_build_response(404, "text/html", "<h1>404</h1>");
    }

    fseek(f, 0L, SEEK_END);
    file_size = ftell(f);
    rewind(f);

    file_data = malloc(file_size + 1);

    if (!file_data) {
        fclose(f);
        return file_server_build_response(500, "text/html", "<h1>Malloc Failed</h1>");
    }

    if ( 1 != fread(file_data, file_size, 1, f)) {
        fclose(f);
        return file_server_build_response(500, "text/html", "<h1>Unable To Read File</h1>");
    }

    const char* mime = file_server_determine_mime(filename);

    char* rsp = file_server_build_response(200, mime, file_data);

    free(file_data);

    return rsp;
}

void file_server_register_file(const char* url, const char* filename) {
    file_members_count++;

    struct FileMember** new_members = (struct FileMember**) malloc(sizeof(struct FileMember) * file_members_count);

    if (file_members_count - 1 > 0) {
        for (int i = 0; i < file_members_count - 1; i++) {
            new_members[i] = File_Server_File_Members[i];
        }
        free(File_Server_File_Members);
    }

    struct FileMember* new_member = (struct FileMember*) malloc(sizeof(struct FileMember));

    new_member->url = url;
    new_member->filename = filename;

    new_members[file_members_count - 1] = new_member;

    File_Server_File_Members = new_members;
}
