#ifndef BITSRTOS_SEM_H
#define BITSRTOS_SEM_H

typedef struct rtx_sem {
    int count;
} rtx_sem_t;

rtx_sem_t *rtx_sem_init(rtx_sem_t *sem, int count);
int rtx_sem_wait(rtx_sem_t *sem);
int rtx_sem_post(rtx_sem_t *sem);
int rtx_sem_getvalue(rtx_sem_t *sem);

#endif