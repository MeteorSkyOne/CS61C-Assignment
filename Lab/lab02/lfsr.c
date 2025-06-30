#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

#define get_bit(x, n) ((x >> n) & 1u)

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t _0 = get_bit(*reg, 0);
    uint16_t _2 = get_bit(*reg, 2);
    uint16_t _3 = get_bit(*reg, 3);
    uint16_t _5 = get_bit(*reg, 5);
    uint16_t n = _0 ^ _2 ^ _3 ^ _5;
    *reg = (n << 15) + (*reg >> 1);
}

