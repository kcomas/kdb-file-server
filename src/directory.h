#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string.h>
#include "./error.h"

const int kdbfs_set_directory(const char* folder);

const bool kdbfs_join_path(struct KDBFS_Request* request);

#endif
