
#include "./file_server.h"

int main(int argc, char* argv[]) {

    file_server_set_directory("./test/");

    char* test_file = file_server_join_path("test.html");

    printf("%s\n", test_file);
}
