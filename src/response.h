#ifndef RESPONSE_H
#define RESPONSE_H

#define KXVER 3
#include "../kdb/k.h"
#include "./request.h"
#include "./util.h"
#include "./error.h"

K kdbfs_create_response_k(struct KDBFS_Request* request);

bool kdbfs_generate_response(struct KDBFS_Request* request);

K kdbfs_redirect_to_index_response();

K kdbfs_not_found_error_response();

K kdbfs_fatal_error_response();

K kdbfs_select_error_response(struct KDBFS_Request* request);

#endif
