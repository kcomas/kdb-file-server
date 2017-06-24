
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
