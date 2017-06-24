#ifndef ERROR_H
#define ERROR_H

#include "./request.h"

enum KDBFS_Errors_Codes {
    KDBFS_SUCCESS,
    KDBFS_REQUEST_MALLOC_FAIL,
    KDBFS_REQUEST_FILE_PATH_MALLOC_FAIL,
    KDBFS_FILE_NOT_FOUND,
    KDBFS_CANNOT_OPEN_FILE,
    KDBFS_CANNOT_CALLOC_FILE_BUFFER,
    KDBFS_FILE_READ_FAILED,
    KDBFS_FILE_HAS_NO_EXTENSION,
    KDBFS_MIME_TYPE_NOT_FOUND
};

struct KDBFS_Error {
    const char* message;
    const int status_code;
};

const struct KDBFS_Error kdbfs_create_error(const char* message, const int status_code);

const struct KDBFS_Error kdbfs_get_error_from_code(int error_code);

const struct KDBFS_Error kdbfs_get_error(struct KDBFS_Request* request);

#endif
