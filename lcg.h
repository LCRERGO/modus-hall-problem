#include <stdint.h>

const uint32_t RNG_a = 1664525;
const uint32_t RNG_c = 1013904223;
uint32_t RNG_state;

union uint32_t_float
{
    uint32_t i;
    float f;
};

void lcg_srand(uint32_t i);
uint32_t lcg_rand();
float float_rand();
