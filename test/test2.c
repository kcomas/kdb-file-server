
#include "../src/file_server.h"

int main(int argc, char** argv) {

    K static_dir = ks("./examples");
    K list_dir = kg(false);
    K url = ks("test.html");

    K rsp = kdbfs_run_request(static_dir, list_dir, url);

    r0(static_dir);
    r0(rsp);

    printf("%s\n", (char*) kS(rsp));

    printf("---\n");

    K static_dir_2 = ks("./examples/");

    K rsp_2 = kdbfs_run_request(static_dir_2, list_dir, url);

    printf("%s\n", (char*) kS(rsp_2));

    r0(list_dir);
    r0(url);
    r0(static_dir_2);
    r0(rsp_2);
    m9();

    return 0;
}
