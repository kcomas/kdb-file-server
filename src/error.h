#ifndef ERROR_H
#define ERROR_H

#include "./request.h"

enum KDBFS_Errors {
    KDBFS_SUCCESS
};

const char* kdbfs_get_error(struct KDBFS_Request* request);

#endif
