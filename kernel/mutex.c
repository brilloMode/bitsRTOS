#include <bitsrt/mutex.h>
#include <bitsrt/rtx.h>

extern rtx_task_t *current_task;

rtx_mutex_t *rtx_mutex_init(rtx_mutex_t *mutex) {
    mutex->owner = NULL;
    mutex->priority = 0;
    return mutex;
}

int rtx_mutex_lock(rtx_mutex_t *mutex) {
    while (mutex->owner) rtx_yield();
    mutex->owner = current_task;
    return 0;
}

int rtx_mutex_unlock(rtx_mutex_t *mutex) {
    mutex->owner = NULL;
    return 0;
}