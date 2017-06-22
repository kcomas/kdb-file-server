
#ifndef FILE_SERVER
#define FILE_SERVER

#define KXVER 3
#include "./k.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct FileMember {
   const char* url;
   const char* filename;
};

struct MimeType {
    const char* ext;
    const char* mime;
};

struct StatusCodeMessage {
    const int code;
    const char* message;
};

void file_server_set_directory(const char* folder);

char* file_server_quick_copy(const char* str);

char* file_server_join_path(const char* path);

const char* file_server_determine_mime(const char* filename);

const char* file_server_determine_status_name(int status);

char* file_server_build_response(const int status_code, const char* mime, const char* body);

char* file_server_load_file(const char* path);

void file_server_register_file(const char* url, const char* filename);

const char* file_server_get_file(const char* url);

K file_server_set_static_dir(K dir);

K file_server_get_file_by_url(K url);

#endif
