
#include "./request.h"

int kdbfs_create_request(const char* static_dir, const bool list_dir, const char* url,  struct KDBFS_Request** request) {

    *request = (struct KDBFS_Request*) malloc(sizeof(struct KDBFS_Request));

    if (!request) {
        return 1;
    }

    (*request)->file_url = url;
    (*request)->static_directory = static_dir;
    (*request)->list_directory = list_dir;

    (*request)->file_path = NULL;
    (*request)->http_body = NULL;
    (*request)->http_headers = NULL;

    (*request)->error_code = 0;

    (*request)->start_time = clock();

    return 0;
}

void kdbfs_destroy_request(struct KDBFS_Request* request) {

    if (request->file_path != NULL) {
        free(request->file_path);
    }

    if (request->http_body != NULL) {
        free(request->http_body);
    }

    if (request->http_headers != NULL) {
        free(request->http_headers);
    }

    free(request);
}

double kdbfs_request_time(struct KDBFS_Request* request) {
    const clock_t end_time = clock();
    return (double)(end_time - request->start_time) / CLOCKS_PER_SEC * 1000;
}
