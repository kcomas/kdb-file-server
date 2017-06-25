#ifndef RESPONSE_H
#define RESPONSE_H

#define KXVER 3
#include "../kdb/k.h"
#include "./request.h"
#include "./util.h"
#include "./error.h"

bool kdbfs_generate_response(struct KDBFS_Request* request);

K kdbfs_error_response(int status_code);

#endif
