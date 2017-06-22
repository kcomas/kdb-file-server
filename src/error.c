
#include "./error.h"

const char* kdbfs_get_error_from_code(const int error_code) {

    switch (error_code) {

        case KDBFS_SUCCESS:
            return "No Error Occured";

        case KDBFS_REQUEST_MALLOC_FAIL:
            return "Failed To Malloc Request Struct";

        case KDBFS_SET_SERVER_FOLDER_FAIL:
            return "Unable To Set Main Server Directory";

        default:
            return "No Error Code Detected, Something Went Wrong";
    }
}

const char* kdbfs_get_error(struct KDBFS_Request* request) {
    return kdbfs_get_error_from_code(request->error_code);
}
