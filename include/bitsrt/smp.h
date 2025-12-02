#ifndef BITSRTOS_SMP_H
#define BITSRTOS_SMP_H

#include <stdint.h>

uint32_t rtx_smp_num_cores(void);
void rtx_smp_init(void);
uint32_t rtx_cpu_id(void);

#endif