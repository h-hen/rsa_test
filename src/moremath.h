#ifndef MOREMATH_H
#define MOREMATH_H

#include <stdbool.h>

#include "types.h"
#include "ui128toa.h"

ui128 Phi(Prime* primesList, int n);

ui128 modInverse(ui128 e, ui128 m);

ui128 productMod(ui128 a, ui128 b, ui128 mod);

ui128 expMod(ui128 base, ui128 exp, ui128 mod);

uint64_t gcd_128(ui128 a, ui128 b);

bool isDivisible(uint64_t a, uint32_t b);

#endif