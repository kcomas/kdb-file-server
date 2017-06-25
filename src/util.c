
#include "./util.h"

size_t kdbfs_get_strings_lengths(size_t** totals_lengths, const int total, const char** strings) {

    size_t total_size = 0;

    *totals_lengths = (size_t*) malloc(sizeof(size_t) * total);

    if (!*totals_lengths) {
        return 0;
    }

    for (int i = 0; i < total; i++) {
        size_t len = strlen(strings[i]);
        (*totals_lengths)[i] = len;
        total_size += len;
    }

    return total_size;
}

bool kdbfs_join_strings(char** dest, const int total, const char** strings) {

    size_t* totals_lengths;

    size_t total_size = kdbfs_get_strings_lengths(&totals_lengths, total, strings);

    if (total_size == 0) {
        return false;
    }

    *dest = (char*) malloc(total_size + 1);

    if (!*dest) {
        return false;
    }

    size_t current_position = 0;

    for (int i = 0; i < total; i++) {

        size_t length = totals_lengths[i];

        if (i == total - 1) {
            length += 1;
        }

        memcpy(*dest + current_position, strings[i], length);
        current_position += totals_lengths[i];
    }

    free(totals_lengths);

    return true;
}


bool kdbfs_join_strings_by_char(char** dest, int total, const char** strings, const char join) {

    const size_t join_len = 1;

    size_t* totals_lengths;

    size_t total_size = kdbfs_get_strings_lengths(&totals_lengths, total, strings);

    if (total_size == 0) {
        return false;
    }

    *dest = (char*) malloc(join_len * total + total_size + 1);

    if(!*dest) {
        return false;
    }

    size_t current_position = 0;

    for (int i = 0; i < total; i++) {

        size_t length = totals_lengths[i];

        if (i == total - 1) {
            length += 1;
        }

        memcpy(*dest + current_position, strings[i], length);
        current_position += totals_lengths[i];
        (*dest)[current_position] = join;
        current_position += join_len;
    }

    (*dest)[current_position] = '\0';

    free(totals_lengths);

    return true;
}
