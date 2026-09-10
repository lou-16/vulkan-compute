#include "log.h"

void Log(const char* type, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (strcmp(type, "error") == 0)
        printf("\033[31m");
    else if (strcmp(type, "warning") == 0)
        printf("\033[33m");
    else
        printf("\033[0m");

    vprintf(fmt, args);
    printf("\033[0m");

    va_end(args);
}