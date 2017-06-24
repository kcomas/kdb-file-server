
#include "./util.h"

bool kdbfs_join_strings(char** dest, const char* str1, const char* str2) {

    const size_t len1 = strlen(str1);
    const size_t len2 = strlen(str2);

    *dest = (char*) malloc(len1 + len2 + 1);

    if (!*dest) {
        return false;
    }

    memcpy(*dest, str1, len1);
    memcpy(*dest + len1, str2, len2 + 1);

    return true;
}

bool kdbfs_join_strings_by_char(char** dest, const char* str1, const char* str2, const char join) {

    const size_t join_len = 1;

    const size_t len1 = strlen(str1);
    const size_t len2 = strlen(str2);

    *dest = (char*) malloc(len1 + join_len + len2 + 1);

    if (!dest) {
        return false;
    }

    memcpy(*dest, str1, len1);
    (*dest)[len1] = join;
    memcpy(*dest + len1 + join_len, str2, len2 + 1);

    return true;
}
