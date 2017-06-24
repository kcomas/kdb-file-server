#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool kdbfs_join_strings(char** dest, const char* str1, const char* str2);

bool kdbfs_join_strings_by_char(char** dest, const char* str1, const char* str2, const char join);

#endif
