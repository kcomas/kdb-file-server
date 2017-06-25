#ifndef RESPONSE_H
#define RESPONSE_H

#define KXVER 3
#include "../kdb/k.h"
#include "./request.h"
#include "./util.h"
#include "./error.h"

bool kdbfs_generate_response(struct KDBFS_Request* request);

K kdbfs_not_found_error_response();

K kdbfs_fatal_error_response();

#endif
