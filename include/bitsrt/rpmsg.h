#ifndef BITSRTOS_RPMSG_H
#define BITSRTOS_RPMSG_H

#include <stdint.h>

typedef struct rpmsg_channel {
    char name[32];
    uint32_t src_addr;
    void *vring_tx;
    void *vring_rx;
    void (*rx_cb)(void *data, uint32_t len, uint32_t src);
} rpmsg_channel_t;

int rpmsg_init(const char *dev_name);
rpmsg_channel_t *rpmsg_channel_create(const char *name, uint32_t src_addr);
void rpmsg_register_callback(rpmsg_channel_t *ch, void (*cb)(void *data, uint32_t len, uint32_t src));
int rpmsg_send(rpmsg_channel_t *ch, const void *data, uint32_t len);

#endif