// Tiny ELF loader stub - loads "module" from memory
void *rtx_module_load(const char *path) {
    printf("[ELF] Loading %s... OK\n", path);
    return (void*)0x20000000;  // Stub address
}

void rtx_module_call(void *module, const char *func, void *arg) {
    printf("[Module] Calling %s\n", func);
    ((void (*)(void*))0x20000000)(arg);
}