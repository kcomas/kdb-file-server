
#include "./util.h"

struct KDBFS_String kdbfs_create_static_string(const char* str) {

    struct KDBFS_String string;
    string.length = strlen(str);
    string.static_str = str;
    string.malloc_str = NULL;

    return string;
}

void kdbfs_prepare_malloc_string(struct KDBFS_String* string) {
    string->length = 0;
    string->malloc_str = NULL;
}

bool kdbfs_destroy_string(struct KDBFS_String* string) {

    if (string->length != 0 && string->malloc_str != NULL) {
        free(string->malloc_str);
        return true;
    }

    return false;
}

const char* kdbfs_get_string(struct KDBFS_String string) {
    if (string.malloc_str == NULL) {
        return string.static_str;
    }

    return string.malloc_str;
}

size_t kdbfs_get_strings_lengths(const int total, struct KDBFS_String* strings) {

    size_t total_size = 0;

    for (int i = 0; i < total; i++) {
        total_size += strings[i].length;
    }

    return total_size;
}

bool kdbfs_join_strings(struct KDBFS_String* dest, const int total, struct KDBFS_String* strings) {

    size_t total_size = kdbfs_get_strings_lengths(total, strings);

    if (total_size == 0) {
        return false;
    }

    dest->malloc_str = (char*) malloc(total_size + 1);
    dest->length = total_size;

    if (!dest->malloc_str) {
        return false;
    }

    size_t current_position = 0;

    for (int i = 0; i < total; i++) {

        size_t length = strings[i].length;

        if (i == total - 1) {
            length += 1;
        }

        memcpy(dest->malloc_str + current_position, kdbfs_get_string(strings[i]), length);
        current_position += strings[i].length;
    }

    return true;
}


bool kdbfs_join_strings_by_char(struct KDBFS_String* dest, const int total, struct KDBFS_String* strings, const char join) {

    const size_t join_len = 1;

    size_t total_size = kdbfs_get_strings_lengths(total, strings);

    if (total_size == 0) {
        return false;
    }

    size_t new_len = join_len * total + total_size;
    dest->malloc_str = (char*) malloc(new_len + 1);
    dest->length = new_len;

    if(!dest->malloc_str) {
        return false;
    }

    size_t current_position = 0;

    for (int i = 0; i < total; i++) {

        size_t length = strings[i].length;

        if (i == total - 1) {
            length += 1;
        }

        memcpy(dest->malloc_str + current_position, kdbfs_get_string(strings[i]), length);
        current_position += strings[i].length;
        (dest->malloc_str)[current_position] = join;
        current_position += join_len;
    }

    (dest->malloc_str)[current_position] = '\0';

    return true;
}

bool kdbfs_join_strings_by_string(struct KDBFS_String* dest, const int total, struct KDBFS_String* strings, const char* join) {

    size_t join_len = strlen(join);

    size_t total_size = kdbfs_get_strings_lengths(total, strings);

    if (total_size == 0) {
        return false;
    }

    size_t new_len = join_len * total + total_size;
    dest->malloc_str = (char*) malloc(new_len + 1);
    dest->length = new_len;

    if (!dest->malloc_str) {
        return false;
    }

    size_t current_position = 0;

    for (int i = 0; i < total; i++) {

        size_t length = strings[i].length;

        if (i == total - 1) {
            join_len += 1;
        }

        memcpy(dest->malloc_str + current_position, kdbfs_get_string(strings[i]), length);
        current_position += strings[i].length;
        memcpy(dest->malloc_str + current_position, join, join_len);
        current_position += join_len;
    }

    return true;
}


bool kdbfs_copy_string(char** dest, const char* source) {

    const size_t len = sizeof(source) + 1;

    *dest = (char*) malloc(len);

    if (!*dest) {
        return false;
    }

    memcpy(*dest, source, len);

    return true;
}
