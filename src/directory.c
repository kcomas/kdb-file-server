
#include "./directory.h"

bool kdbfs_join_path(struct KDBFS_Request* request) {

    const char* strings[] = { request->static_directory, request->file_url };

    bool ret = kdbfs_join_strings(&request->file_path, 2, strings);

    if (!ret) {
       request->error_code = KDBFS_REQUEST_FILE_PATH_MALLOC_FAIL;
       return false;
    }

    return true;
}


bool kdbfs_list_directory(struct KDBFS_Request* request) {


}
