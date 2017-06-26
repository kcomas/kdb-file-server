#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include "./util.h"

struct KDBFS_Request {
    const char* file_url;
    const char* static_directory;
    bool list_directory;
    struct KDBFS_string file_path;
    struct stat file_stat;
    int total_dir_contents;
    struct dirent **dir_contents;
    const char* mime_type;
    long http_body_size;
    struct KDBFS_string http_body;
    int error_code;
    struct KDBFS_string http_headers;
    clock_t start_time;
    clock_t end_time;
    struct KDBFS_string response;
};

int kdbfs_create_request(const char* static_dir, const bool list_dir, const char* url,  struct KDBFS_Request** request);

void kdbfs_destroy_request(struct KDBFS_Request* request);

void kdbfs_clean_response_parts(struct KDBFS_Request* request);

void kdbfs_end_timer(struct KDBFS_Request* request);

double kdbfs_request_time(struct KDBFS_Request* request);

#endif
