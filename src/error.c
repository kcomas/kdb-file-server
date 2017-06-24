
#include "./error.h"


const struct KDBFS_Error kdbfs_create_error(const int error_code, const char* message, const int status_code) {

    struct KDBFS_Error err = {
        message,
        status_code,
        error_code
    };

    return err;
}

const struct KDBFS_Error kdbfs_get_error_from_code(int error_code) {

    switch (error_code) {

        case KDBFS_SUCCESS:
            return kdbfs_create_error(error_code, "No Error Occured", 200);

        case KDBFS_REQUEST_MALLOC_FAIL:
            return kdbfs_create_error(error_code, "Failed To Malloc Request Struct", 500);

        case KDBFS_FILE_NOT_FOUND:
            return kdbfs_create_error(error_code, "File Or Directory Not Found", 404);

        case KDBFS_CANNOT_OPEN_FILE:
            return kdbfs_create_error(error_code, "Unable To Open File", 500);

        case KDBFS_CANNOT_CALLOC_FILE_BUFFER:
            return kdbfs_create_error(error_code, "Unable To Calloc File Buffer", 500);

        case KDBFS_FILE_READ_FAILED:
            return kdbfs_create_error(error_code, "Unable To Read File", 500);

        case KDBFS_FILE_HAS_NO_EXTENSION:
            return kdbfs_create_error(error_code, "File Does Not Have An Extension Cannot Determine Mime", 200);

        case KDBFS_MIME_TYPE_NOT_FOUND:
            return kdbfs_create_error(error_code, "Mime Type Not Found For File", 200);

        default:
            return kdbfs_create_error(error_code, "No Error Code Detected, Something Went Wrong", 200);
    }
}

const struct KDBFS_Error kdbfs_get_error(struct KDBFS_Request* request) {
    return kdbfs_get_error_from_code(request->error_code);
}
