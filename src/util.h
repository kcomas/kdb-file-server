#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct KDBFS_String {
    size_t length;
    const char* static_str;
    char* malloc_str;
};

struct KDBFS_String kdbfs_create_static_string(const char* str);

void kdbfs_prepare_malloc_string(struct KDBFS_String* string);

bool kdbfs_destroy_string(struct KDBFS_String* string);

const char* kdbfs_get_string(struct KDBFS_String string);

size_t kdbfs_get_strings_lengths(const int total, struct KDBFS_String* strings);

bool kdbfs_join_strings(struct KDBFS_String* dest, const int total, struct KDBFS_String* strings);

bool kdbfs_join_strings_by_char(struct KDBFS_String* dest, const int total, struct KDBFS_String* strings, const char join);

bool kdbfs_join_strings_by_string(struct KDBFS_String* dest, const int total, struct KDBFS_String* strings, const char* join);

#endif
