
#include "../src/directory.h"
#include "../src/stat.h"
#include "../src/file.h"

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

void print_file_data(struct KDBFS_Request* request) {

    printf("%s\n", request->http_body);

}

void print_mime_type(struct KDBFS_Request* request) {

    printf("Mime Type: %s\n", request->mime_type);
    printf("\n");

}

int main(int argc, char** argv) {

    struct KDBFS_Request* example_request_1;
    bool rst;

    int code = kdbfs_create_request("./examples/", true, "test.html", &example_request_1);

    if (code) {
        goto ERROR;
    }

    rst = kdbfs_join_path(example_request_1);

    if (!rst) {
        goto ERROR;
    }

    print_file_info(example_request_1);

    rst = kdbfs_stat_request(example_request_1);

    if (!rst) {
        goto ERROR;
    }

    print_file_stat(example_request_1);

    rst = kdbfs_load_file(example_request_1);

    if (!rst) {
        goto ERROR;
    }

    print_file_data(example_request_1);

    rst = kdbfs_determine_mime_type(example_request_1);

    if (!rst) {
        goto ERROR;
    }

    print_mime_type(example_request_1);

    ERROR:
    kdbfs_destroy_request(example_request_1);
    printf("%s\n", kdbfs_get_error(example_request_1).message);
    return example_request_1->error_code;
}
