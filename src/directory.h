#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "./error.h"

bool kdbfs_set_directory(const char* folder);

bool kdbfs_join_path(struct KDBFS_Request* request);

#endif
