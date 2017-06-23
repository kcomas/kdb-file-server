
#include <stdio.h>
#include "../src/directory.h"
#include "../src/stat.h"

void print_file_info(struct KDBFS_Request* request) {

    printf("File Url: %s\n", request->file_url);
    printf("Directory: %s\n", request->static_directory);
    printf("Joined Path: %s\n", request->file_path);
    printf("List Dir?: %d\n", request->list_directory);
    printf("\n");
}

void print_file_stat(struct KDBFS_Request* request) {

    printf("Is File: %d\n", kdbfs_is_file(request));
    printf("Is Dir: %d\n", kdbfs_is_directory(request));
    printf("\n");

}

int main(int argc, char** argv) {

    struct KDBFS_Request* example_request_1;
    bool rst;

    int code = kdbfs_create_request("./examples/", true, "test.html", &example_request_1);

    if (code) {
        printf("%s\n", kdbfs_get_error_from_code(code));
        return 1;
    }

    rst = kdbfs_join_path(example_request_1);

    if (!rst) {
        printf("%s\n", kdbfs_get_error(example_request_1));
        return 1;
    }

    print_file_info(example_request_1);

    rst = kdbfs_stat_request(example_request_1);

    if (!rst) {
        printf("%s\n", kdbfs_get_error(example_request_1));
        return 1;
    }

    print_file_stat(example_request_1);

    kdbfs_destroy_request(example_request_1);

    return 0;
}
