
#include "./file_server.h"

int main(int argc, char* argv[]) {

    file_server_set_directrory("./test/");

    char* test_file = file_server_join_path("test.html");

    printf("%s", test_file);
}
