#ifndef PRIMES_H
#define PRIMES_H

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "moremath.h"
#include "types.h"

Prime* getPrimes(int n);
Prime generatePrime(int size_bits);
bool isPrime(Prime n);

#endif