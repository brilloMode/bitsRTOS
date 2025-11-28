#ifndef BITSRTOS_RTX_H
#define BITSRTOS_RTX_H

#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "sem.h"
#include "mutex.h"
#include "pthread.h"
#include "smp.h"

typedef struct rtx_task rtx_task_t;

struct rtx_task {
    const char *name;
    void (*entry)(void*);
    void *arg;
    uint32_t stack[CONFIG_STACK_SIZE];
    uint32_t *sp;
    uint8_t priority;
    bool running;
    uint32_t affinity_mask;
};

void rtx_init(void);
void rtx_start(void);
rtx_task_t *rtx_task_create(const char *name, void (*entry)(void*), void *arg, uint8_t prio, uint32_t stack_size);
void rtx_task_set_affinity(rtx_task_t *task, uint32_t core_mask);
uint32_t rtx_cpu_id(void);
void rtx_delay(uint32_t ms);

#endif