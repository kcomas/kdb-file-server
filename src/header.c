
#include "./header.h"

const static int kdbfs_status_messages_length = 3;

const static struct KDBFS_Status_Messages kdbfs_status_messages[] = {
    {200, "OK"},
    {404, "Not Found"},
    {500, "Internal Server Error"}
};

const char* kdbfs_get_status_message(int status_code) {

    const char* status_msg = NULL;

    for (int i = 0; i < kdbfs_status_messages_length; i++) {
        if (status_code == kdbfs_status_messages[i].status_code) {
            status_msg = kdbfs_status_messages[i].status_message;
            break;
        }
    }

    return status_msg;
}

bool kdbfs_create_status_line(struct KDBFS_Header* header, int status_code) {

    const char* status_msg = kdbfs_get_status_message(status_code);

    if (status_msg == NULL) {
        return false;
    }

    char status_code_str[4];

    snprintf(status_code_str, 4, "%d", status_code);

    const char* strings[] = { "HTTP/1.1", status_code_str, status_msg };

    bool ret = kdbfs_join_strings_by_char(&header->status_line, 3, strings, ' ');

    if (!ret) {
        return false;
    }

    return true;
}

bool kdbfs_create_content_line(struct KDBFS_Header* header, const char* mime_type) {

    const char* strings[] = { "Content-Type: ", mime_type, "; charset=utf-8" };

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

    (*header)->status_line = NULL;
    (*header)->content_line = NULL;

    return true;
}

void kdbfs_destory_header(struct KDBFS_Header* header) {

    if (header->status_line != NULL) {
        free(header->status_line);
    }

    if (header->content_line != NULL) {
        free(header->content_line);
    }

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

    const char* strings[] = { header->status_line, header->content_line, "" };

    ret = kdbfs_join_strings_by_string(&request->http_headers, 3, strings, "\r\n");

    kdbfs_destory_header(header);

    if (!ret) {
        request->error_code = KDBFS_CANNOT_MERGE_HEADER;
        return false;
    }

    return true;
}
