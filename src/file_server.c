
#include "./file_server.h"

static struct FileMember File_Server_File_Members[];

static char* file_server_directory = NULL;

void file_server_set_directory(const char* folder) {

    if (file_server_directory != NULL) {
        free(file_server_directory);
    }

    file_server_directory = (char*) malloc(strlen(folder) + 1);
    strcpy(file_server_directory, folder);
}

char* file_server_join_path(const char* path) {
    if (file_server_directory == NULL) {
        fprintf(stderr, "ERROR: file_server_directory not set\n");
        char* path2 = (char*) malloc(strlen(path) + 1);
        strcpy(path2, path);
        return path2;
    }

    char* joined = (char*) malloc(strlen(file_server_directory) + strlen(path) + 1);
    strcpy(joined, file_server_directory);
    strcat(joined, path);
    return joined;
}
