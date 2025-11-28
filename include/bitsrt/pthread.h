#ifndef BITSRTOS_PTHREAD_H
#define BITSRTOS_PTHREAD_H

#include <bitsrt/rtx.h>

typedef rtx_task_t pthread_t;

int pthread_create(pthread_t *thread, const void *attr, void *(*start_routine)(void*), void *arg);
int pthread_join(pthread_t thread, void **retval);

#endif