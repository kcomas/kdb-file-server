
#ifndef FILE_SERVER
#define FILE_SERVER

#define KXVER 3
#include "./k.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct FileMember {
   const char* filename;
   const char* url;
};

struct MimeType {
    const char* ext;
    const char* mime;
};

void file_server_set_directory(const char* folder);

const char* file_server_join_path(const char* path);

const char* file_server_determine_mime(const char* filename);

const char* file_server_load_file(const char* path);

void file_server_register_file(const char* url, const char* filename);

K file_server_get_file(K url);

#endif
