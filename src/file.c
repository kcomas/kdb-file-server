
#include "./file.h"

bool kdbfs_load_file(struct KDBFS_Request* request) {

    FILE *fp;

    fp = fopen(request->file_path, "rb");

    if (!fp) {
        request->error_code = KDBFS_CANNOT_OPEN_FILE;
        return false;
    }

    fseek(fp, 0L, SEEK_END);
    request->http_body_size = ftell(fp);
    rewind(fp);

    request->http_body = (char*) malloc(request->http_body_size + 1);
    memset(request->http_body, '\0', request->http_body_size + 1);

    if (!request->http_body) {
        fclose(fp);
        request->error_code = KDBFS_CANNOT_CALLOC_FILE_BUFFER;
        return false;
    }

    size_t ret = fread(request->http_body, request->http_body_size, 1, fp);

    if (1 != ret) {
        fclose(fp);
        request->error_code = KDBFS_FILE_READ_FAILED;
        return false;
    }

    fclose(fp);

    return true;
}
