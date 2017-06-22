
#include "./file_server.h"

int main(int argc, char* argv[]) {

    file_server_set_directory("./test/");

    const char* test_file_name = file_server_join_path("test.html");

    printf("File %s\n", test_file_name);

    const char* test_mime_type = file_server_determine_mime(test_file_name);

    printf("Mime %s\n", test_mime_type);
}
