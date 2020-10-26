#ifndef LCG_H
#define LCG_H
#include <stdint.h>


union uint32_t_float
{
    uint32_t i;
    float f;
};

void lcg_srand(uint32_t i);
uint32_t lcg_rand();
float float_rand();
#endif
