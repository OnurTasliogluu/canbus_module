#ifndef OT_CANBUS_SERVER
#define OT_CANBUS_SERVER

#include <stdint.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

typedef struct {
    int32_t socket;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;
    uint8_t interface_name[32];
} ot_canbus_server_t;

typedef enum {
    OT_CANBUS_START,
    OT_CANBUS_PREOP,
    OT_CANBUS_STOP,
} ot_canbus_states;

ot_canbus_server_t *ot_canbus_server_create();
int32_t ot_canbus_server_init(ot_canbus_server_t *this, uint8_t *interface_name);
void ot_canbus_server_loop(ot_canbus_server_t *this);
int32_t ot_canbus_server_deinit(ot_canbus_server_t *this);
int32_t ot_canbus_server_destroy(ot_canbus_server_t *this);

void ot_canbus_server_set_net_interface_name(ot_canbus_server_t *this, uint8_t *interface_name);
uint8_t *ot_canbus_server_get_net_interface_name(ot_canbus_server_t *this);

#endif