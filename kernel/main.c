#include <bitsrt/rtx.h>
#include <stdio.h>  // Provided by BSP

void idle_task(void *arg) {
    while (1) {
        printf("bitsRTOS idle tick\n");
        rtx_delay(1000);
    }
}

void smp_demo(void *arg) {
    printf("Core %lu: SMP demo running\n", rtx_cpu_id());
    while (1) rtx_delay(500);
}

int main(void) {
    printf("bitsRTOS v0.7-smp\nCopyright (c) 2025 brilloMode - MIT\n");

    rtx_init();

    rtx_task_create("idle", idle_task, NULL, 0, 256);
    for (int i = 0; i < 4; ++i) {
        char name[16]; 
        snprintf(name, sizeof(name), "smp%d", i);
        rtx_task_t *t = rtx_task_create(name, smp_demo, NULL, 5, 512);
        rtx_task_set_affinity(t, 1U << (i % 4));
    }

    rtx_start();
    return 0;
}