#ifndef RSA_H
#define RSA_H

#include <stdio.h>

#include "primes.h"
#include "moremath.h"
#include "types.h"
#include "ui128toa.h"

Key getPublicKey(Prime* primeList, int n);

Key getPrivateKey(Prime* primeList, int n, ui128 N, unsigned int e);

Key insertPublicKey(ui128 N, unsigned int e);

Key insertPrivateKey(ui128 N, ui128 d);

ui128 getD(Key key);

ui128 getN(Key key);

ui128 encrypt(Key key, ui128 message);

ui128 decrypt(Key key, Prime* primeList, int size, ui128 cypher);

ui128 simpleDecrypt(Key key, ui128 cypher);

unsigned int getE(Key key);

void printPublicKey(Key key);

void printPrivateKey(Key key);

#endif