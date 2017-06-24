
#include "./header.h"

const static int kdbfs_status_messages_length = 3;

const static struct KDBFS_Status_Messages kdbfs_status_messages[] = {
    {200, "OK"},
    {404, "Not Found"},
    {500,"Internal Server Error"}
};
