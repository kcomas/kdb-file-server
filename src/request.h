#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

struct KDBFS_Request {
    const char* file_url;
    const char* static_directory;
    bool list_directory;
    char* file_path;
    bool malloc_file_path;
    struct stat file_stat;
    const char* mime;
    int code;
    const char* message;
    long file_size;
    char* file_data;
    bool malloc_file_data;
    int error_code;
    char* http_headers;
    bool malloc_http_headers;
};

const int kdbfs_create_request(const char* static_dir, const bool list_dir, const char* url,  struct KDBFS_Request** request);

void kdbfs_destroy_request(struct KDBFS_Request* request);

#endif
