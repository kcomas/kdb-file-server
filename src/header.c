
#include "./header.h"

const static int kdbfs_status_messages_length = 3;

const static struct KDBFS_Status_Messages kdbfs_status_messages[] = {
    {200, "OK"},
    {404, "Not Found"},
    {500, "Internal Server Error"}
};

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

    // ret = kdbfs_create_status_line(header, kdbfs_get_error(request).status_code);

}
