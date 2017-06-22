
#include "./file_server.h"

int main(int argc, char* argv[]) {

    file_server_set_directory("./examples/");

    char* test_file_name = file_server_join_path("test.html");
    printf("File %s\n\n", test_file_name);

    const char* test_mime_type = file_server_determine_mime(test_file_name);
    printf("Mime %s\n\n", test_mime_type);

    test_mime_type = file_server_determine_mime("test.txt");
    printf("Mime %s\n\n", test_mime_type);

    char* broken_rsp = file_server_load_file("asd4as1254");
    printf("%s\n\n", broken_rsp);

    char* example_response = file_server_load_file("test.html");
    printf("%s\n\n", example_response);

    file_server_register_file("test", "test.html");
    file_server_register_file("test_text", "test.txt");
    file_server_register_file("", "alert.html");

    char* ex_alert = file_server_get_file("");
    printf("%s\n\n", ex_alert);

    char* ex_text = file_server_get_file("test_text");
    printf("%s\n\n", ex_text);

    char* ex_html = file_server_get_file("test");
    printf("%s\n\n", ex_html);
}
