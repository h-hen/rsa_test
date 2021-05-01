#include "moremath.h"

/*Calcula o inverso multiplicativo modular e^-1 mod m utilizando o algoritmo euclidiano extendido.*/
ui128 modInverse(ui128 e, ui128 m){
    
    ui128 m0 = m;
    i128 y = 0, x = 1;

    while (e > 1) {
        
        i128 q = e / m;
        i128 t = m;

        m = e % m;
        e = t;
        t = y;
 
        y = x - q * y;
        x = t;
    }

    if (x < 0)
        return x + m0;
 
    return (ui128) x;
}

/*Calcula o tociente de Euler [Φ(n)] para os primos concedidos.*/
ui128 Phi(Prime* primesList, int n){

    ui128 phi = 1;

    for(int i = 0; i < n; i++)
        phi *= (primesList[i]-1);

    return phi;
}

/*Calcula o módulo de um produto ab mod m usando propriedade distributivas.*/
ui128 productMod(ui128 a, ui128 b, ui128 mod){

    ui128 output = 0;

    a = a % mod;

    while(b > 0){
        
        if (b & 1)
            output = (output + a) % mod;

        a = (a * 2) % mod;

        b >>= 1;
    }

    return output % mod;
}

/*Calcula exponenciação modular de a^b mod m usando a técnica de dividir para conquistar.*/
ui128 expMod(ui128 base, ui128 exp, ui128 mod){

    ui128 output = 1;

    base %= mod;

    if(base == 0) return 0;

    while(exp > 0){

        if(exp & 1)
            output = productMod(output, base, mod);

        exp >>= 1;
        base = productMod(base, base, mod) % mod;
    }

    return output;
}

/*Calcula o máximo divisor comum entre dois inteiros de 128-bits.*/
uint64_t gcd_128(ui128 a, ui128 b){
 
    if (b == 0)
        return a;

    return gcd_128(b, a%b);
}

/*Verifica a divisibilidade de dois inteiros.*/
bool isDivisible(uint64_t a, uint32_t b){

    bool output = a%b;

    return !(output);
}

