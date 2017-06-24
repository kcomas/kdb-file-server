
#include "./file.h"
#include "./error.h"

const static int kdbfs_mimes_length = 3;

const static struct KDBFS_Mime_Types kdbfs_mimes[] = {
    {"html", "text/html"},
    {"txt", "text/plain"},
    {"js", "application/javascript"}
};

bool kdbfs_determine_mime_type(struct KDBFS_Request* request) {

    const char* last_dot = strrchr(request->file_url, '.');

    if (!last_dot || last_dot == request->file_url) {
        request->error_code = KDBFS_FILE_HAS_NO_EXTENSION;
        request->mime_type = "application/octet-stream";
        return false;
    }

    const char* ext = last_dot + 1;

    for (int i = 0; i < kdbfs_mimes_length; i++) {
        if (strcmp(kdbfs_mimes[i].file_ext, ext) == 0) {
            request->mime_type = kdbfs_mimes[i].mime;
            return true;
        }
    }

    request->error_code = KDBFS_MIME_TYPE_NOT_FOUND;
    request->mime_type = "application/octet-stream";
    return false;
}

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