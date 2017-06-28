
#include "./header.h"

const static int kdbfs_status_messages_length = 3;

const static struct KDBFS_Status_Messages kdbfs_status_messages[] = {
    {200, "OK"},
    {404, "Not Found"},
    {500, "Internal Server Error"}
};

struct KDBFS_String kdbfs_get_status_message(int status_code) {

    for (int i = 0; i < kdbfs_status_messages_length; i++) {
        if (status_code == kdbfs_status_messages[i].status_code) {
            return kdbfs_create_static_string(kdbfs_status_messages[i].status_message);
        }
    }

    struct KDBFS_String err;
    err.length = 0;
    return err;
}

bool kdbfs_create_status_line(struct KDBFS_Header* header, int status_code) {

    struct KDBFS_String status_msg = kdbfs_get_status_message(status_code);

    if (status_msg.length == 0) {
        return false;
    }

    char status_code_str[4];

    snprintf(status_code_str, 4, "%d", status_code);

    struct KDBFS_String strings[] = {
        kdbfs_create_static_string("HTTP/1.1"),
        kdbfs_create_static_string(status_code_str),
        status_msg
    };

    bool ret = kdbfs_join_strings_by_char(&header->status_line, 3, strings, ' ');

    if (!ret) {
        return false;
    }

    return true;
}

bool kdbfs_create_content_line(struct KDBFS_Header* header, struct KDBFS_String mime_type) {

    struct KDBFS_String strings[] = {
        kdbfs_create_static_string("Content-Type: "),
        mime_type,
        kdbfs_create_static_string("; charset=utf-8")
    };

    bool ret = kdbfs_join_strings(&header->content_line, 3, strings);

    if(!ret) {
        return false;
    }

    return true;
}

bool kdbfs_create_header(struct KDBFS_Header** header) {

    *header = (struct KDBFS_Header*) malloc(sizeof(struct KDBFS_Header));

    if (!*header) {
        return false;
    }

    kdbfs_prepare_malloc_string(&(*header)->status_line);
    kdbfs_prepare_malloc_string(&(*header)->content_line);

    return true;
}

void kdbfs_destory_header(struct KDBFS_Header* header) {

    kdbfs_destroy_string(&header->status_line);

    kdbfs_destroy_string(&header->content_line);

    free(header);
}

bool kdbfs_build_headers(struct KDBFS_Request* request) {

    struct KDBFS_Header* header;

    bool ret = kdbfs_create_header(&header);

    if (!ret) {
        request->error_code = KDBFS_HEADER_MALLOC_FAIL;
        return false;
    }

    ret = kdbfs_create_status_line(header, kdbfs_get_error(request).status_code);

    if (!ret) {
        request->error_code = KDBFS_CANNOT_CREATE_HEADER_STATUS;
        kdbfs_destory_header(header);
        return false;
    }

    ret = kdbfs_create_content_line(header, request->mime_type);

    if (!ret) {
        request->error_code = KDBFS_CANNOT_CREATE_HEADER_CONTENT;
        kdbfs_destory_header(header);
        return false;
    }

    struct KDBFS_String strings[] = {
        header->status_line,
        header->content_line,
        kdbfs_create_static_string("")
    };

    ret = kdbfs_join_strings_by_string(&request->http_headers, 3, strings, "\r\n");

    kdbfs_destory_header(header);

    if (!ret) {
        request->error_code = KDBFS_CANNOT_MERGE_HEADER;
        return false;
    }

    return true;
}
