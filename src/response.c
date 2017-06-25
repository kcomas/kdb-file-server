
#include "./response.h"

bool kdbfs_generate_response(const char** response_string, struct KDBFS_Request* request) {

    const char* strings[] = { request->http_headers, request->http_body };

    bool ret = kdbfs_join_strings(response_string, 2, strings);

}
