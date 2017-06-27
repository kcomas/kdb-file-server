
#include "./request.h"

int kdbfs_create_request(const char* static_dir, const bool list_dir, const char* url,  struct KDBFS_Request** request) {

    *request = (struct KDBFS_Request*) malloc(sizeof(struct KDBFS_Request));

    if (!request) {
        return 1;
    }

    (*request)->file_url = kdbfs_create_static_string(url);
    (*request)->static_directory = kdbfs_create_static_string(static_dir);
    (*request)->list_directory = list_dir;
    kdbfs_prepare_malloc_string(&(*request)->file_path);
    (*request)->total_dir_contents = 0;
    (*request)->dir_contents = NULL;
    (*request)->http_body_size = 0;
    (*request)->error_code = 0;
    kdbfs_prepare_malloc_string(&(*request)->http_body);
    kdbfs_prepare_malloc_string(&(*request)->http_headers);
    kdbfs_prepare_malloc_string(&(*request)->response);
    (*request)->start_time = clock();

    return 0;
}

void kdbfs_destroy_request(struct KDBFS_Request* request) {

    kdbfs_destroy_string(&request->file_path);

    if (request->dir_contents != NULL) {
        free(request->dir_contents);
    }

    if (!kdbfs_destroy_string(&request->response)) {
        kdbfs_clean_response_parts(request);
    }

    free(request);
}

void kdbfs_clean_response_parts(struct KDBFS_Request* request) {
    kdbfs_destroy_string(&request->http_body);
    kdbfs_destroy_string(&request->http_headers);

}

void kdbfs_end_timer(struct KDBFS_Request* request) {
    request->end_time = clock();
}

double kdbfs_request_time(struct KDBFS_Request* request) {
    return (double)(request->end_time - request->start_time) / CLOCKS_PER_SEC * 1000;
}
