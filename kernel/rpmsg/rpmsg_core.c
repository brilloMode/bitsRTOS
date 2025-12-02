#include <bitsrt/rpmsg.h>
#include <string.h>
#include <stddef.h>

static rpmsg_channel_t channels[32];  // Max 32 channels
static int num_channels = 0;

int rpmsg_init(const char *dev_name) {
    // Init MU (Messaging Unit) — SoC-specific in BSP
    return 0;
}

rpmsg_channel_t *rpmsg_channel_create(const char *name, uint32_t src_addr) {
    if (num_channels >= 32) return NULL;
    rpmsg_channel_t *ch = &channels[num_channels++];
    strncpy(ch->name, name, 32);
    ch->src_addr = src_addr;
    ch->vring_tx = (void*)0xC00000;  // OCRAM vring (SoC-specific)
    ch->vring_rx = ch->vring_tx + 0x4000;
    return ch;
}

void rpmsg_register_callback(rpmsg_channel_t *ch, void (*cb)(void *data, uint32_t len, uint32_t src)) {
    ch->rx_cb = cb;
}

int rpmsg_send(rpmsg_channel_t *ch, const void *data, uint32_t len) {
    if (len > 496) return -1;  // VirtIO limit
    // Zero-copy: copy to vring_tx desc (simplified)
    memcpy(ch->vring_tx, data, len);
    // Kick MU IRQ to A-core
    *(volatile uint32_t*)0x44580000 = 1;  // MU_A_IRQ (i.MX 8M Plus example)
    return 0;
}

// RX interrupt handler (called from BSP MU ISR)
void rpmsg_rx_isr(rpmsg_channel_t *ch) {
    uint32_t len = *(uint32_t*)(ch->vring_rx);  // Stub len
    void *data = (void*)(ch->vring_rx + 4);
    if (ch->rx_cb) ch->rx_cb(data, len, 0x100);  // Src stub
}