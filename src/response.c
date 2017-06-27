
#include "./response.h"

K kdbfs_create_response_k(struct KDBFS_Request* request) {

    return kp(request->response.malloc_str);
}

bool kdbfs_generate_response(struct KDBFS_Request* request) {

    struct KDBFS_string strings[] = { request->http_headers, request->http_body };

    bool ret = kdbfs_join_strings(&request->response, 2, strings);

    if (!ret) {
        request->error_code = KDBFS_CANNOT_CREATE_RESPONSE;
        return false;
    }

    kdbfs_clean_response_parts(request);

    return true;
}

K kdbfs_redirect_to_index_response() {

    return kp("HTTP/1.1 302 Found\r\nLocation: /index.html\r\n\r\n");
}

K kdbfs_not_found_error_response() {

    return kp("HTTP/1.1 404 Not Found\r\nContnet-Type: text/html\r\n\r\n<h1 style=\"text-align: center\">404</h1>");
}

K kdbfs_fatal_error_response() {

    return kp("HTTP/1.1 500 Internal Server Error\r\nContnet-Type: text/html\r\n\r\n<h1 style=\"text-align: center\">500</h1>");
}

K kdbfs_select_error_response(struct KDBFS_Request* request) {

    struct KDBFS_Error err = kdbfs_get_error(request);

    switch (err.status_code) {
        case 302:
            return kdbfs_redirect_to_index_response();
        case 404:
            return kdbfs_not_found_error_response();
        case 500:
            return kdbfs_fatal_error_response();
        default:
            return kdbfs_fatal_error_response();
    }

}
