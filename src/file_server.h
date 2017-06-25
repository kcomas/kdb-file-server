#ifndef FILE_SERVER_H
#define FILE_SERVER_H

#include "./response.h"
#include "./directory.h"

K kdbfs_run_request(K static_dir, K list_dir, K url);

#endif
