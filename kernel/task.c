#include <bitsrt/rtx.h>
#include <stdio.h>

rtx_task_t *rtx_task_create(const char *name, void (*entry)(void*), void *arg, uint8_t prio, uint32_t stack_size) {
    static rtx_task_t tasks[CONFIG_MAX_TASKS];
    static int next_id = 0;
    rtx_task_t *task = &tasks[next_id++];
    task->name = name;
    task->entry = entry;
    task->arg = arg;
    task->priority = prio;
    task->running = false;
    task->affinity_mask = 0xFFFFFFFF;  // All cores
    // Init stack pointer (stub)
    task->sp = &task->stack[stack_size / 4 - 1];
    printf("Task %s created (prio %d)\n", name, prio);
    return task;
}

void rtx_task_set_affinity(rtx_task_t *task, uint32_t core_mask) {
    task->affinity_mask = core_mask;
}