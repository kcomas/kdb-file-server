
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

K kdbfs_not_found_error_response() {

    return kp("HTTP/1.1 400 Not Found\r\nContnet-Type: text/html\r\n\r\n<h1 style=\"text-align: center\">400</h1>");
}

K kdbfs_fatal_error_response() {

    return kp("HTTP/1.1 500 Internal Server Error\r\nContnet-Type: text/html\r\n\r\n<h1 style=\"text-align: center\">500</h1>");
}

K kdbfs_select_error_response(struct KDBFS_Request* request) {

    struct KDBFS_Error err = kdbfs_get_error(request);

    switch (err.status_code) {
        case 404:
            return kdbfs_not_found_error_response();
        case 500:
            return kdbfs_fatal_error_response();
        default:
            return kdbfs_fatal_error_response();
    }

}
