
#include "../src/file_server.h"

int main(int argc, char** argv) {

    char* examples_str;
    kdbfs_copy_string(&examples_str, "./examples");

    K static_dir = ks(examples_str);
    free(examples_str);

    K list_dir = kg(false);

    char* file_str;
    bool ret = kdbfs_copy_string(&file_str, "test.html");

    if (!ret) {
        return 1;
    }

    K url = ks(file_str);
    free(file_str);

    K rsp = kdbfs_run_request(static_dir, list_dir, url);

    r0(static_dir);
    r0(rsp);

    printf("%s\n", (char*) kS(rsp));

    printf("---\n");

    char* examples_2_str;
    ret = kdbfs_copy_string(&examples_2_str, "./examples/");

    if (!ret) {
        return 1;
    }

    K static_dir_2 = ks(examples_2_str);
    free(examples_2_str);

    K rsp_2 = kdbfs_run_request(static_dir_2, list_dir, url);

    printf("%s\n", (char*) kS(rsp_2));

    r0(list_dir);
    r0(url);
    r0(static_dir_2);
    r0(rsp_2);
    m9();

    return 0;
}
