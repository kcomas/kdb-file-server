
#include "./file_server.h"

K kdbfs_run_request(K static_dir, K list_dir, K url) {

    struct KDBFS_Request* request;

    int code = kdbfs_create_request(static_dir->s, kG(list_dir), list_dir->s, &request);

    if (code) {
        struct KDBFS_Error err = kdbfs_get_error_from_code(code);
        kdbfs_error_to_stderr(err);
        return kdbfs_fatal_error_response();
    }

}
