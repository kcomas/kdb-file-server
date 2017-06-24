
#include "./error.h"

const char* kdbfs_get_error_from_code(const int error_code) {

    switch (error_code) {

        case KDBFS_SUCCESS:
            return "No Error Occured";

        case KDBFS_REQUEST_MALLOC_FAIL:
            return "Failed To Malloc Request Struct";

        case KDBFS_FILE_NOT_FOUND:
            return "File Or Directory Not Found";

        case KDBFS_CANNOT_OPEN_FILE:
            return "Unable To Open File";

        case KDBFS_CANNOT_CALLOC_FILE_BUFFER:
            return "Unable To Calloc File Buffer";

        case KDBFS_FILE_READ_FAILED:
            return "Unable To Read File";

        case KDBFS_FILE_HAS_NO_EXTENSION:
            return "File Does Not Have An Extension Cannot Determine Mime";

        case KDBFS_MIME_TYPE_NOT_FOUND:
            return "Mime Type Not Found For File";

        default:
            return "No Error Code Detected, Something Went Wrong";
    }
}

const char* kdbfs_get_error(struct KDBFS_Request* request) {
    return kdbfs_get_error_from_code(request->error_code);
}
