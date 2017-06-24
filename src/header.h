#ifndef HEADER_H
#define HEADER_H

#include "./error.h"

struct KDBFS_Header {
    const char* status_line;
    const char* content_line;
};

struct KDBFS_Status_Messages {
    const int status_code;
    const char* status_message;
};

bool kdbfs_create_status_line(struct KDBFS_Header* header, int status_code);

bool kdbfs_create_content_line(struct KDBFS_Header* header, const char* mime_type);

bool kdbfs_create_header(struct KDBFS_Header** header);

bool kdbfs_destory_header(struct KDBFS_Header* header);

bool kdbfs_build_headers(struct KDBFS_Request* request);

#endif
