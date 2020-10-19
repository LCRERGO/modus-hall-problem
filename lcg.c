#include <stdint.h>

#include "lcg.h"

const uint32_t RNG_a = 1664525;
const uint32_t RNG_c = 1013904223;
uint32_t RNG_state;

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
