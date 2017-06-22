#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>
#include <stdlib.h>

struct KDBFS_Request {
    const char* url;
    char* filepath;
    const char* mime;
    const int code;
    const char* message;
    const long file_size;
    char* file_data;
    int error_code;
};

const int kdbfs_create_request(const char* url, struct KDBFS_Request* request);

const bool kdbfs_destroy_request(struct KDBFS_Request* request);

#endif
