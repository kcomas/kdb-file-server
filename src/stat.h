#ifndef STAT_H
#define STAT_H

#include "./error.h"

const bool kdbfs_is_file(struct KDBFS_Request* request);

const bool kdbfs_is_directory(struct KDBFS_Request* request);

const bool kdbfs_stat_request(struct KDBFS_Request* request);

#endif
