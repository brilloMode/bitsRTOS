#ifndef BITSRTOS_MUTEX_H
#define BITSRTOS_MUTEX_H

#include <stdint.h>

typedef struct rtx_task rtx_task_t;

typedef struct rtx_mutex {
    rtx_task_t *owner;
    uint8_t priority;
} rtx_mutex_t;

rtx_mutex_t *rtx_mutex_init(rtx_mutex_t *mutex);
int rtx_mutex_lock(rtx_mutex_t *mutex);
int rtx_mutex_unlock(rtx_mutex_t *mutex);

#endif