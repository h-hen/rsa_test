#include "primes.h"

/*Retorna um vetor de n números primos.*/
Prime* getPrimes(int n){

    if(n > 16 && n < 2) return 0;

    Prime* primeList = (Prime*) malloc(sizeof(Prime) * n);

    for(int i = 0; i < n; i++){

        primeList[i] = generatePrime(128/n);

        for(int j = 0; j < i; j++)
            if(primeList[i] == primeList[j]){

                --i;

                break;
            }        
    }

    return primeList;
}

/*Gera um primo aleatório de tamanho size_bits.*/
Prime generatePrime(int size_bits){

    Prime biggestNum = (Prime) pow(2, size_bits) - 1;

    Prime random = rand();

    Prime prime = random % biggestNum + 1;

    while(isPrime(prime) == 0){

        prime++;
    }

    if(prime < 2)
        prime = generatePrime(size_bits);

    return prime;
}

/*Verifica a primalidade de n.*/
bool isPrime(Prime n){

    bool output = 0;

    uint32_t sqrtOfN = (uint32_t) floor(sqrt(n)), i = 1;

    output += isDivisible(n, 2);
    output += isDivisible(n, 3);

    while(6*i-1 <= sqrtOfN){

        output += isDivisible(n, (6*i+1));
        output += isDivisible(n, (6*i-1));

        i++;
    }

    return output == 0;
}
