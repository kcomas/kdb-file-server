
#include "./file_server.h"

static int file_members_count = 0;

static struct FileMember File_Server_File_Members[];

static char* file_server_directory = NULL;

const static struct MimeType File_Server_Mime_Types[2] = {
    {"html", "text/html"},
    {"js", "application/javascript"}
};

const static struct StatusCodeMessage File_Server_Status_Messages[2] = {
    {200, "OK"},
    {404, "Not Found"}
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

    for (int i = 0; i < 2; i++) {
        if (strcmp(File_Server_Mime_Types[i].ext, ext) == 0) {
            return File_Server_Mime_Types[i].mime;
        }
    }

    return "application/octet-stream";
}

const char* file_server_build_headers(const int status_code, const char* mime, const char* body) {

}

const char* file_server_load_file(const char* filename) {

    FILE* f;
    long file_size;
    char* file_data;

    char* fullname = file_server_join_path(filename);

    f = fopen(fullname, "rb");

    free(fullname);

    if (!f) {
        return file_server_build_headers(404, "text/html", "<h1>404</h1>");
    }

    return "";
}
