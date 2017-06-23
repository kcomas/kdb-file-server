
#include "./file.h"

const bool kdbfs_load_file(struct KDBFS_Request* request) {

    FILE *fp;

    fp = fopen(request->file_path, "rb");

    if (!fp) {
        request->error_code = KDBFS_CANNOT_OPEN_FILE;
        return false;
    }

    fseek(fp, 0L, SEEK_END);
    request->file_size = ftell(fp);
    rewind(fp);

    request->file_data = (char*) calloc(1, request->file_size + 1);

    if (!request->file_data) {
        fclose(fp);
        request->error_code = KDBFS_CANNOT_CALLOC_FILE_BUFFER;
        return false;
    }

    request->calloc_file_data = true;

    size_t ret = fread(request->file_data, request->file_size, 1, fp);

    if (1 != ret) {
        fclose(fp);
        request->error_code = KDBFS_FILE_READ_FAILED;
        return false;
    }

    fclose(fp);

    return true;
}
