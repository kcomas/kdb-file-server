
#include "./response.h"

bool kdbfs_generate_response(struct KDBFS_Request* request) {

    const char* strings[] = { request->http_headers, request->http_body };

    bool ret = kdbfs_join_strings(&request->response, 2, strings);

    if (!ret) {
        request->error_code = KDBFS_CANNOT_CREATE_RESPONSE;
        return false;
    }

    kdbfs_clean_response_parts(request);

    return true;
}

K kdbfs_error_response() {

    return kp("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n<h1 style=\"text-align: center\">500</h1>");

}
