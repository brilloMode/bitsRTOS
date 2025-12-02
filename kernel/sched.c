#include <bitsrt/rtx.h>
#include <stdio.h>

rtx_task_t *current_task;

void rtx_yield(void) {
    // Context switch stub
    asm volatile("ecall");  // Trap to scheduler
}

void rtx_init(void) {
    // Init ready queues, timer
    printf("Scheduler initialized\n");
}

void rtx_start(void) {
    // Start first task
    rtx_yield();  // Enter scheduler
}