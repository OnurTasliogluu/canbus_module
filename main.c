#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ot_canbus_server.h"

pid_t canbus_server;
ot_canbus_server_t *test = NULL;

// control-c 

void all_destroy() {
    ot_canbus_server_deinit(test);
    ot_canbus_server_destroy(test);
}

int main(int argc, char *argv[]) {

    test = ot_canbus_server_create();

    ot_canbus_server_init(test, "vcan0");

    // thread create and join   ot_canbus_server_loop
    ot_canbus_server_loop(test);


    ot_canbus_server_deinit(test);
    ot_canbus_server_destroy(test);

    return 0;
}