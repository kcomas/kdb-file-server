
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

void file_server_set_directory(const char* folder);

char* file_server_join_path(const char* path);

char* file_server_load_file(const char* path);

void file_server_register_file(const char* url, const char* filename);

K file_server_get_file(K url);

#endif
