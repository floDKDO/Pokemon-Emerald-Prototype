#ifndef __LOG__FUNCTIONS__H__
#define __LOG__FUNCTIONS__H__

#include <stdio.h>

void print_C_version(void);

//TODO : use SDL_Log ?
#define LOG(string) do{ fprintf(stderr, string); }while(0)

#endif // __LOG__FUNCTIONS__H__
