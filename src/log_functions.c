#include "log_functions.h"

void print_C_version(void)
{
    #ifdef __STDC_VERSION__
    if(__STDC_VERSION__ == 202000)
        LOG("C language version = C23\n");
    else if (__STDC_VERSION__ == 201710L)
        LOG("C language version = C17\n");
    else if (__STDC_VERSION__ == 201112L)
        LOG("C language version = C11\n");
    else if (__STDC_VERSION__ == 199901L)
        LOG("C language version = C99\n");
    #else
        LOG("C language version = C90\n");
    #endif
}
