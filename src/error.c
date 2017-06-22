
#include "./error.h"

const char* kdbfs_get_error(struct KDBFS_Request* request) {

    switch (request->error_code) {

        case KDBFS_SUCCESS:
            return "No Error";

        default:
            return "No Error Code Detected Something went wrong";
    }

}
