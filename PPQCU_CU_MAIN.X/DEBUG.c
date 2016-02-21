#include "DEBUG.h"

void DEBUG_init(int baud) {
#ifdef DEBUG

#endif /*DEBUG*/
}

void DEBUG_printf(char * msg, int level) {
#ifdef DEBUG
    if (level < DEBUG_LEVEL) {

    }
#endif /*DEBUG*/
}

