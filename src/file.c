
#include "./file.h"
#include "./error.h"

const static int kdbfs_mimes_length = 3;

const static struct KDBFS_Mime_Types kdbfs_mimes[] = {
    {"html", "text/html"},
    {"txt", "text/plain"},
    {"js", "application/javascript"}
};

bool kdbfs_determine_mime_type(struct KDBFS_Request* request) {

    const char* last_dot = strrchr(kdbfs_get_string(request->file_url), '.');

    if (!last_dot || last_dot == kdbfs_get_string(request->file_url)) {
        request->error_code = KDBFS_FILE_HAS_NO_EXTENSION;
        request->mime_type = kdbfs_create_static_string("application/octet-stream");
        return false;
    }

    const char* ext = last_dot + 1;

    for (int i = 0; i < kdbfs_mimes_length; i++) {
        if (strcmp(kdbfs_mimes[i].file_ext, ext) == 0) {
            request->mime_type = kdbfs_create_static_string(kdbfs_mimes[i].mime);
            return true;
        }
    }

    request->error_code = KDBFS_MIME_TYPE_NOT_FOUND;
    request->mime_type = kdbfs_create_static_string("application/octet-stream");
    return false;
}

bool kdbfs_load_file(struct KDBFS_Request* request) {

    FILE *fp;

    fp = fopen(kdbfs_get_string(request->file_path), "rb");

    if (!fp) {
        request->error_code = KDBFS_CANNOT_OPEN_FILE;
        return false;
    }

    request->http_body.malloc_str = (char*) malloc(request->file_stat.st_size + 1);
    request->http_body.length = (size_t) request->file_stat.st_size;

    memset(request->http_body.malloc_str, '\0', request->http_body.length + 1);

    if (!request->http_body.malloc_str) {
        fclose(fp);
        request->error_code = KDBFS_CANNOT_MALLOC_FILE_BUFFER;
        return false;
    }

    size_t ret = fread(request->http_body.malloc_str, request->http_body.length, 1, fp);

    if (1 != ret) {
        fclose(fp);
        request->error_code = KDBFS_FILE_READ_FAILED;
        return false;
    }

    fclose(fp);

    return true;
}
