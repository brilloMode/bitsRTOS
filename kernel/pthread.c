#include <bitsrt/pthread.h>
#include <bitsrt/rtx.h>

int pthread_create(pthread_t *thread, const void *attr, void *(*start_routine)(void*), void *arg) {
    rtx_task_t *task = rtx_task_create("pthread", (void (*)(void*))start_routine, arg, 1, 512);
    if (!task) return -1;
    *thread = *task;
    return 0;
}

int pthread_join(pthread_t thread, void **retval) {
    // Stub: wait indefinitely
    while (1) rtx_delay(100);
    return 0;
}