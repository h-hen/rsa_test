#ifndef TYPES_H
#define TYPES_H

#include <inttypes.h>
#include <stdint.h>

#define UINT128_MAX UINT64_MAX * UINT64_MAX

typedef __uint128_t ui128;
typedef __int128_t i128;
typedef uint32_t Prime;

typedef void* Key;

#endif