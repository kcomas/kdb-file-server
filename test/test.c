
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

void exit_error(struct KDBFS_Request* request) {

    struct KDBFS_Error err = kdbfs_get_error(request);
    kdbfs_destroy_request(request);
    printf("%s\n", err.message);
    exit(err.error_code);

}

int main(int argc, char** argv) {

    struct KDBFS_Request* example_request_1;
    bool rst;

    int code = kdbfs_create_request("./examples/", true, "test.html", &example_request_1);

    if (code) {
        exit_error(example_request_1);
    }

    rst = kdbfs_join_path(example_request_1);

    if (!rst) {
        exit_error(example_request_1);
    }

    print_file_info(example_request_1);

    rst = kdbfs_stat_request(example_request_1);

    if (!rst) {
        exit_error(example_request_1);
    }

    print_file_stat(example_request_1);

    rst = kdbfs_load_file(example_request_1);

    if (!rst) {
        exit_error(example_request_1);
    }

    print_file_data(example_request_1);

    rst = kdbfs_determine_mime_type(example_request_1);

    if (!rst) {
        exit_error(example_request_1);
    }

    print_mime_type(example_request_1);

    const char* strings[] = {"12", "34", "56", ""};

    char* simple_join;
    rst = kdbfs_join_strings(&simple_join, 4, strings);

    if (!rst) {
        printf("Error Could Not Join Strings");
        return 1;
    }

    printf("Joined Strings: %s\n", simple_join);

    free(simple_join);

    char* join_by_space;
    rst = kdbfs_join_strings_by_char(&join_by_space, 4, strings, ' ');

    if (!rst) {
        printf("Error Could Not Join Strings By Space");
        return 1;
    }

    printf("Joined Strings By Space: %s\n", join_by_space);

    free(join_by_space);

    char* join_by_lines;
    rst = kdbfs_join_strings_by_string(&join_by_lines, 4, strings, "--");

    if (!rst) {
        printf("Could Not Join Strings By String");
        return 1;
    }

    printf("Joined Strings By Strings: %s\n", join_by_lines);

    free(join_by_lines);

    kdbfs_destroy_request(example_request_1);

    return 0;
}
