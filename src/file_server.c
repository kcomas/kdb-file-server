
#include "./file_server.h"

static struct FileMember File_Server_File_Members[];

static char* file_server_directory = NULL;

const static struct MimeType File_Server_Mime_Types[2] = {
    {"html", "text/html"},
    {"js", "application/javascript"}
};

void file_server_set_directory(const char* folder) {

    if (file_server_directory != NULL) {
        free(file_server_directory);
    }

    file_server_directory = (char*) malloc(strlen(folder) + 1);
    strcpy(file_server_directory, folder);
}

const char* file_server_join_path(const char* path) {
    if (file_server_directory == NULL) {
        fprintf(stderr, "ERROR: file_server_directory not set\n");
        return path;
    }

    char* joined = (char*) malloc(strlen(file_server_directory) + strlen(path) + 1);
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
