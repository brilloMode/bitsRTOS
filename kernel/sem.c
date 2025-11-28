#include <bitsrt/sem.h>

rtx_sem_t *rtx_sem_init(rtx_sem_t *sem, int count) {
    sem->count = count;
    return sem;
}

int rtx_sem_wait(rtx_sem_t *sem) {
    while (sem->count <= 0) rtx_yield();
    sem->count--;
    return 0;
}

int rtx_sem_post(rtx_sem_t *sem) {
    sem->count++;
    return 0;
}

int rtx_sem_getvalue(rtx_sem_t *sem) {
    return sem->count;
}