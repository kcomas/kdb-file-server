#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include "./request.h"

enum KDBFS_Errors_Codes {
    KDBFS_SUCCESS,
    KDBFS_REQUEST_MALLOC_FAIL,
    KDBFS_REQUEST_FILE_PATH_MALLOC_FAIL,
    KDBFS_FILE_NOT_FOUND,
    KDBFS_CANNOT_OPEN_FILE,
    KDBFS_CANNOT_MALLOC_FILE_BUFFER,
    KDBFS_FILE_READ_FAILED,
    KDBFS_FILE_HAS_NO_EXTENSION,
    KDBFS_MIME_TYPE_NOT_FOUND,
    KDBFS_HEADER_MALLOC_FAIL,
    KDBFS_CANNOT_CREATE_HEADER_STATUS,
    KDBFS_CANNOT_CREATE_HEADER_CONTENT,
    KDBFS_CANNOT_MERGE_HEADER,
    KDBFS_CANNOT_CREATE_RESPONSE,
    KDBFS_SCANDIR_FAIL
};

struct KDBFS_Error {
    const char* message;
    const int status_code;
    const int error_code;
};

const struct KDBFS_Error kdbfs_create_error(const int error_code, const char* message, const int status_code);

const struct KDBFS_Error kdbfs_get_error_from_code(int error_code);

const struct KDBFS_Error kdbfs_get_error(struct KDBFS_Request* request);

void kdbfs_error_to_stderr(struct KDBFS_Error err);

#endif
