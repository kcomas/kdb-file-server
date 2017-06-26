
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

        case KDBFS_CANNOT_MALLOC_FILE_BUFFER:
            return kdbfs_create_error(error_code, "Unable To Calloc File Buffer", 500);

        case KDBFS_FILE_READ_FAILED:
            return kdbfs_create_error(error_code, "Unable To Read File", 500);

        case KDBFS_FILE_HAS_NO_EXTENSION:
            return kdbfs_create_error(error_code, "File Does Not Have An Extension Cannot Determine Mime", 200);

        case KDBFS_MIME_TYPE_NOT_FOUND:
            return kdbfs_create_error(error_code, "Mime Type Not Found For File", 200);

        case KDBFS_HEADER_MALLOC_FAIL:
            return kdbfs_create_error(error_code, "Unable To Malloc Header", 500);

        case KDBFS_CANNOT_CREATE_HEADER_STATUS:
            return kdbfs_create_error(error_code, "Cannot Create Http Header Status", 500);

        case KDBFS_CANNOT_CREATE_HEADER_CONTENT:
            return kdbfs_create_error(error_code, "Cannot Create Http Header Content", 500);

        case KDBFS_CANNOT_MERGE_HEADER:
            return kdbfs_create_error(error_code, "Cannot Join Header Strings", 500);

        case KDBFS_CANNOT_CREATE_RESPONSE:
            return kdbfs_create_error(error_code, "Cannot Merge Headers And Response", 500);

        case KDBFS_SCANDIR_FAIL:
            return kdbfs_create_error(error_code, "Scandir Cannot List Directory", 500);

        case KDBFS_INCORRECT_FILE_TYPE:
            return kdbfs_create_error(error_code, "Requested File From Url Is Not A File Or Directory", 500);

        case KDBFS_REDIRECT_TO_INDEX:
            return kdbfs_create_error(error_code, "Request Will Be Redirected To Index", 302);

        default:
            return kdbfs_create_error(error_code, "No Error Code Detected, Something Went Wrong", 500);
    }
}

const struct KDBFS_Error kdbfs_get_error(struct KDBFS_Request* request) {
    return kdbfs_get_error_from_code(request->error_code);
}

void kdbfs_error_to_stderr(struct KDBFS_Error err) {
    fprintf(stderr, "\nError: %s\n", err.message);
}
