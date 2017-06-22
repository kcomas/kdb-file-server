#ifndef ERROR_H
#define ERROR_H

#include "./request.h"

enum KDBFS_Errors {
    KDBFS_SUCCESS,
    KDBFS_REQUEST_MALLOC_FAIL,
    KDBFS_SET_SERVER_FOLDER_FAIL
};

const char* kdbfs_get_error_request(struct KDBFS_Request* request);

const char* kdbfs_get_error_from_code(int error_code);

#endif
