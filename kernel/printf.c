#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

// Minimal printf stub - BSPs should override this
__attribute__((weak)) int printf(const char *fmt, ...) {
    (void)fmt;
    // BSP should provide printf implementation
    return 0;
}

__attribute__((weak)) int snprintf(char *str, size_t size, const char *fmt, ...) {
    (void)str;
    (void)size;
    (void)fmt;
    // BSP should provide snprintf implementation
    return 0;
}

