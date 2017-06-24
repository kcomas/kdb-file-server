#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <string.h>
#include "./error.h"

struct KDBFS_Mime_Types {
    const char* file_ext;
    const char* mime;
};

bool kdbfs_determine_mime_type(struct KDBFS_Request* request);

bool kdbfs_load_file(struct KDBFS_Request* request);

#endif
