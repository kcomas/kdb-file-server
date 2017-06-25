#ifndef FILE_SERVER_H
#define FILE_SERVER_H

#include "./response.h"
#include "./stat.h"
#include "./directory.h"
#include "./file.h"

bool kdbfs_file_operations(struct KDBFS_Request* request);

bool kdbfs_directory_operations(struct KDBFS_Request* request);

K kdbfs_run_request(K static_dir, K list_dir, K url);

#endif
