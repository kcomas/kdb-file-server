
#include "./directory.h"

static char* kdbfs_file_directory = NULL;

const int kdbfs_set_directory(const char* folder) {
    if (kdbfs_file_directory != NULL) {
        free(kdbfs_file_directory);
    }

    const size_t len = strlen(folder) + 1;

    kdbfs_file_directory = (char*) malloc(len);

    if (!kdbfs_file_directory) {
        return 2;
    }

    memcpy(kdbfs_file_directory, folder, len);

    return 0;
}

const bool kdbfs_join_path(struct KDBFS_Request* request) {

}
