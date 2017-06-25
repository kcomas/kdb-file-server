#ifndef RESPONSE_H
#define RESPONSE_H

#include "./request.h"
#include "./util.h"

bool kdbfs_generate_response(const char** response_string, struct KDBFS_Request* request);

#endif
