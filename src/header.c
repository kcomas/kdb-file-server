
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

bool kdbfs_build_headers(struct KDBFS_Request* request) {

    struct KDBFS_Header* header;

    bool created = kdbfs_create_header(&header);

    if (!created) {
        request->error_code = KDBFS_HEADER_MALLOC_FAIL;
        return false;
    }

}
