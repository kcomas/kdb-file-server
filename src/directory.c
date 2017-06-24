
#include "./directory.h"
#include "./util.h"

bool kdbfs_join_path(struct KDBFS_Request* request) {

    bool ret = kdbfs_join_two_strings(&request->file_path, request->static_directory, request->file_url);

    if (!ret) {
       request->error_code = KDBFS_REQUEST_FILE_PATH_MALLOC_FAIL;
       return false;
    }

    return true;
}
