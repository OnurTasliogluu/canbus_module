#include <stdlib.h>
#include <string.h>


#include "ot_canbus_server.h"

static void ot_canbus_server_enum_start();
static void ot_canbus_server_enum_preop();
static void ot_canbus_server_enum_stop();

static void (*ot_canbus_server_operation_list[3])() = { ot_canbus_server_enum_start, ot_canbus_server_enum_preop, ot_canbus_server_enum_stop };

static void ot_canbus_server_parser(ot_canbus_server_t *this, uint8_t *data);




ot_canbus_server_t *ot_canbus_server_create() {
    ot_canbus_server_t *this = malloc(sizeof(ot_canbus_server_t));

    if(this == NULL) {
        // error logging
        return NULL;
    }

    return this;
}

int32_t ot_canbus_server_init(ot_canbus_server_t *this, uint8_t *interface_name) {

    if ((this->socket = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return -1;
    }

    ot_canbus_server_set_net_interface_name(this, interface_name);

    strcpy(this->ifr.ifr_name, this->interface_name);
    ioctl(this->socket, SIOCGIFINDEX, &(this->ifr));
    memset(&(this->addr), 0, sizeof(this->addr));
    this->addr.can_family = AF_CAN;
    this->addr.can_ifindex = this->ifr.ifr_ifindex;

    if (bind(this->socket, (struct sockaddr *)&(this->addr), sizeof(this->addr)) < 0) {
        perror("Bind");
        return 1;
    }
    return 0;
}

static void ot_canbus_server_parser(ot_canbus_server_t *this, uint8_t *data) {
    // PACKET PARSER then operation
}

static void ot_canbus_server_operation() {

}

void ot_canbus_server_loop(ot_canbus_server_t *this) {
    uint8_t *data;
    struct can_frame frame;
    size_t size;
    //for(;;) {
        printf("recv");
        size = recv(this->socket, &(this->frame), sizeof(struct can_frame), 0);

        if (size < 0) {
            perror("Read");
            return NULL;
        }
        // get packet
        //ot_canbus_server_parser(this, frame.data);
    //}

    return NULL;
}

int32_t ot_canbus_server_deinit(ot_canbus_server_t *this) {
    return 0;
}

int32_t ot_canbus_server_destroy(ot_canbus_server_t *this) {
    return 0;
}

static void ot_canbus_server_enum_start() {

}

static void ot_canbus_server_enum_preop() {

}

static void ot_canbus_server_enum_stop() {

}

void ot_canbus_server_set_net_interface_name(ot_canbus_server_t *this, uint8_t *interface_name) {
    strncpy(this->interface_name, interface_name, sizeof(this->interface_name));
}

uint8_t *ot_canbus_server_get_net_interface_name(ot_canbus_server_t *this) {
    return this->interface_name;
}