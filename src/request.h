#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include "./util.h"

struct KDBFS_Request {
    struct KDBFS_String file_url;
    struct KDBFS_String static_directory;
    bool list_directory;
    struct KDBFS_String file_path;
    struct stat file_stat;
    int total_dir_contents;
    struct dirent **dir_contents;
    struct KDBFS_String mime_type;
    long http_body_size;
    struct KDBFS_String http_body;
    int error_code;
    struct KDBFS_String http_headers;
    clock_t start_time;
    clock_t end_time;
    struct KDBFS_String response;
};

int kdbfs_create_request(const char* static_dir, const bool list_dir, const char* url,  struct KDBFS_Request** request);

void kdbfs_destroy_request(struct KDBFS_Request* request);

void kdbfs_clean_response_parts(struct KDBFS_Request* request);

void kdbfs_end_timer(struct KDBFS_Request* request);

double kdbfs_request_time(struct KDBFS_Request* request);

#endif
