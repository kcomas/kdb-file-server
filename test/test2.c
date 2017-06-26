
#include "../src/file_server.h"

int main(int argc, char** argv) {

    K static_dir = ks("./examples");
    K list_dir = kg(false);
    K url = ks("test.html");

    K rsp = kdbfs_run_request(static_dir, list_dir, url);

    printf("%s\n", rsp->s);

    return 0;
}
