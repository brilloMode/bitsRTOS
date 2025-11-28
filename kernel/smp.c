#include <bitsrt/smp.h>

uint32_t rtx_smp_num_cores(void) {
#ifdef BITSRTOS_SMP
    return 4;  // Stub
#else
    return 1;
#endif
}

uint32_t rtx_cpu_id(void) {
    uint32_t id;
#ifdef ARCH_RISCV64
    asm("csrr %0, mhartid" : "=r"(id));
#else
    id = 0;
#endif
    return id;
}

void rtx_smp_init(void) {
    printf("SMP: %lu cores online\n", rtx_smp_num_cores());
}