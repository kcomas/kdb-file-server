
#include "./request.h"

const int kdbfs_create_request(const char* url, struct KDBFS_Request* request) {

    request = (struct KDBFS_Request*) malloc(sizeof(struct KDBFS_Request));

    if (!request) {
        return 1;
    }

    request->url = url;

    return 0;
}
