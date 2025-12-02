void _start(void);
void bsp_init(void);
extern int main(void);

void _start(void) {
    bsp_init();
    main();
    while (1);
}