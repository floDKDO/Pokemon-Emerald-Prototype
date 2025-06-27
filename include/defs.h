#ifndef __DEFS__H__
#define __DEFS__H__

#include <stdlib.h>

#define NCHK(op, type) do{ if ((op) == NULL){fprintf(stderr, type); exit(EXIT_FAILURE);} }while(0)
#define CHK(op, type) do{ if ((op) < 0){fprintf(stderr, type); exit(EXIT_FAILURE);} }while(0)

#ifndef DEBUG
#define DEBUG
#endif // DEBUG

#define TILE_SIZE 16
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


#endif // __DEFS__H__
