#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>

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

bool kdbfs_create_request(const char* url, struct KDBFS_Request* request);

#endif
