#include <stdint.h>

#include "lcg.h"

void
lcg_srand(uint32_t i)
{
    RNG_state = i;
}

uint32_t
lcg_rand()
{
    RNG_state = RNG_state * RNG_a + RNG_c;
    return RNG_state;
}

float
float_rand()
{
    union uint32_t_float tmp;

    tmp.i = (lcg_rand() & 0x007fffff) | 0x3f800000;
    return tmp.f-1;
}
