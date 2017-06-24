#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool kdbfs_join_two_strings(char** dest, const char* str1, const char* str2);

bool kdbfs_join_two_strings_by_char(char** dest, const char* str1, const char* str2, const char join);

size_t kdbfs_get_strings_lengths(size_t** totals_lengths, const int total, const char** strings);

bool kdbfs_join_strings(char** dest, const int total, const char** strings);

bool kdbfs_join_strings_by_char(char** dest, int total, const char** strings, const char join);

#endif
