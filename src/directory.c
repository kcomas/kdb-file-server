
#include "./directory.h"

const bool kdbfs_join_path(struct KDBFS_Request* request) {

    const size_t file_len = sizeof(request->file_url);
    const size_t dir_len = sizeof(request->static_directory);

    request->file_path = (char*) malloc(file_len + dir_len + 1);

    if (!request->file_path) {
       request->error_code = KDBFS_REQUEST_FILE_PATH_MALLOC_FAIL;
       return false;
    }

    memcpy(request->file_path, request->file_url, file_len);
    memcpy(request->file_path + file_len, request->static_directory, dir_len + 1);

    return true;
}
