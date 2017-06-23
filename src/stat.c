
#include "./stat.h"

bool kdbfs_is_file(struct KDBFS_Request* request) {
    return S_ISREG(request->file_stat.st_mode);
}

bool kdbfs_is_directory(struct KDBFS_Request* request) {
    return S_ISDIR(request->file_stat.st_mode);
}

bool kdbfs_stat_request(struct KDBFS_Request* request) {

    int ret = stat(request->file_path, &request->file_stat);

    if (ret < 0) {
        request->error_code = KDBFS_FILE_NOT_FOUND;
        return false;
    }

    return true;
}
