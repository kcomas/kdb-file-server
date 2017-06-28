#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include "./error.h"
#include "./util.h"

struct KDBFS_Header {
    struct KDBFS_String status_line;
    struct KDBFS_String content_line;
};

struct KDBFS_Status_Messages {
    const int status_code;
    const char* status_message;
};

struct KDBFS_String kdbfs_get_status_message(int status_code);

bool kdbfs_create_status_line(struct KDBFS_Header* header, int status_code);

bool kdbfs_create_content_line(struct KDBFS_Header* header, struct KDBFS_String mime_type);

bool kdbfs_create_header(struct KDBFS_Header** header);

void kdbfs_destory_header(struct KDBFS_Header* header);

bool kdbfs_build_headers(struct KDBFS_Request* request);

#endif
