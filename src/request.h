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
    struct stat file_stat;
    const char* mime_type;
    int status_code;
    const char* message;
    long http_body_size;
    char* http_body;
    int error_code;
    char* http_headers;
};

int kdbfs_create_request(const char* static_dir, const bool list_dir, const char* url,  struct KDBFS_Request** request);

void kdbfs_destroy_request(struct KDBFS_Request* request);

#endif
