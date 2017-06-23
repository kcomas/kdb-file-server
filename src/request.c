
#include "./request.h"

const int kdbfs_create_request(const char* static_dir, const bool list_dir, const char* url,  struct KDBFS_Request** request) {

    *request = (struct KDBFS_Request*) malloc(sizeof(struct KDBFS_Request));

    if (!request) {
        return 1;
    }

    (*request)->file_url = url;
    (*request)->static_directory = static_dir;
    (*request)->list_directory = list_dir;

    (*request)->malloc_file_path = false;
    (*request)->malloc_file_data = false;
    (*request)->malloc_http_headers = false;

    return 0;
}
