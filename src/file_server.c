
#include "./file_server.h"

static const int kdbfs_total_fns = 5;

bool (*kdbfs_fns[]) (struct KDBFS_Request* request) = {
    kdbfs_join_path,
    kdbfs_stat_request,
    kdbfs_file_dir_split,
    kdbfs_build_headers,
    kdbfs_generate_response
};

bool kdbfs_file_operations(struct KDBFS_Request* request) {

    bool rst = kdbfs_load_file(request);

    if (!rst) {
        return false;
    }

    rst = kdbfs_determine_mime_type(request);

    return rst;
}

bool kdbfs_directory_operations(struct KDBFS_Request* request) {

    bool rst = kdbfs_list_directory(request);

    if (!rst) {
        return false;
    }

    return false;
}

bool kdbfs_file_dir_split(struct KDBFS_Request* request) {

    if (kdbfs_is_file(request)) {
        return kdbfs_file_operations(request);
    } else if (kdbfs_is_directory(request)) {
        if (request->list_directory) {
            return kdbfs_directory_operations(request);
        } else {
            request->error_code = KDBFS_REDIRECT_TO_INDEX;
            return false;
        }
    }

    request->error_code = KDBFS_INCORRECT_FILE_TYPE;
    return false;
}

K kdbfs_run_request(K static_dir, K list_dir, K url) {

    struct KDBFS_Request* request;

    int code = kdbfs_create_request(static_dir->s, kG(list_dir), list_dir->s, &request);

    if (code) {
        struct KDBFS_Error err = kdbfs_get_error_from_code(code);
        kdbfs_error_to_stderr(err);
        return kdbfs_fatal_error_response();
    }

    bool rst;
    K rsp;

    for (int i = 0; i < kdbfs_total_fns; i++) {
        rst = (*kdbfs_fns[i])(request);
        if (!rst) {
            rsp = kdbfs_select_error_response(request);
            kdbfs_destroy_request(request);
            return rsp;
        }
    }

    rsp = kdbfs_create_response_k(request);

    kdbfs_destroy_request(request);

    return rsp;
}
