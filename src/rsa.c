#include "rsa.h"

#define STD_E 65537

typedef struct PublicKey{

    ui128 N;
    unsigned int e;

} PublicKey;

typedef struct PrivateKey{

    ui128 N;
    ui128 d;

} PrivateKey;

/*Gera o número N.*/
static ui128 genN(Prime* primeList, int n){

    ui128 N = 1;

    for(int i = 0; i < n; i++)
        N *= primeList[i];

    return N;
}

/*Gera o número e.*/
static unsigned int genE(Prime* primeList, int n){

    ui128 phi = Phi(primeList, n);

    unsigned int e;

    printf("\nInsira um valor para e (0 - padrao/1 - aleatorio): ");
    scanf("%u", &e);

    if(e){

        e = rand();

        while(gcd_128((ui128) e, phi) != 1)
            e++;

    } else e = STD_E;

    char* strPhi = ui128toa(phi);
    printf("Phi: %s\n", strPhi);

    free(strPhi);

    return e;
}

/*Gera a chave pública <N,e>.*/
Key getPublicKey(Prime* primeList, int n){

    PublicKey* publicKey = (PublicKey*) malloc(sizeof(PublicKey));

    publicKey->N = genN(primeList, n);
    publicKey->e = genE(primeList, n);

    return publicKey;
}

/*Gera a chave privada <N,d>*/
Key getPrivateKey(Prime* primeList, int n, ui128 N, unsigned int e){

    PrivateKey* privateKey = (PrivateKey*) malloc(sizeof(PrivateKey));

    privateKey->N = N;
    privateKey->d = modInverse(e, Phi(primeList, n));

    return privateKey;
}

/*Permite ao usuário definir a chave pública.*/
Key insertPublicKey(ui128 N, unsigned int e){

    PublicKey* publicKey = (PublicKey*) malloc(sizeof(PublicKey));

    publicKey->N = N;
    publicKey->e = e;

    return publicKey;
}

/*Permite ao usuário definir a chave privada.*/
Key insertPrivateKey(ui128 N, ui128 d){

    PrivateKey* privateKey = (PrivateKey*) malloc(sizeof(PrivateKey));

    privateKey->N = N;
    privateKey->d = d;

    return privateKey;
}

/*Retorna d de uma chave.*/
ui128 getD(Key key){

    PrivateKey* privateKey = (PrivateKey*) key;

    return privateKey->d;
}

/*Retorna N de uma chave.*/
ui128 getN(Key key){

    PublicKey* publicKey = (PublicKey*) key;

    return publicKey->N;
}

/*Encripta uma mensagem.*/
ui128 encrypt(Key key, ui128 message){

    return (ui128) expMod(message, getE(key), getN(key));
}

/*Desencripta uma mensagem.*/
ui128 decrypt(Key key, Prime* primeList, int size, ui128 cypher){

    ui128 d = getD(key), output = 0, Mc; 

    Prime* reduced = (Prime*) malloc(sizeof(Prime)*size);
    Prime* msgPartial = (Prime*) malloc(sizeof(Prime)*size);
    
    for(int i = 0; i < size; i++){

        reduced[i] = d % (primeList[i] - 1);
        msgPartial[i] = expMod(cypher, reduced[i], primeList[i]);

        Mc = getN(key)/primeList[i];

        // output += msgPartial[i] * Mc * modInverse(Mc % primeList[i], primeList[i]);
        output += productMod(msgPartial[i], productMod(Mc, modInverse(Mc % primeList[i], primeList[i]), getN(key)), getN(key));
    }    

    free(msgPartial);
    free(reduced);

    return output % getN(key);
}

/*Desencripta uma função sem o TCM, sem a necessidade de inserir manualmente os primos*/
ui128 simpleDecrypt(Key key, ui128 cypher){

    return (ui128) expMod(cypher, getD(key), getN(key));
}

/*Retorna e de uma chave.*/
unsigned int getE(Key key){

    PublicKey* publicKey = (PublicKey*) key;

    return publicKey->e;
}

/*Imprime a chave pública.*/
void printPublicKey(Key key){

    PublicKey* publicKey = (PublicKey*) key;

    char* N = ui128toa(publicKey->N);

    printf("Chave publica: <%s,%d>\n", N, publicKey->e);

    free(N);
}

/*Imprime a chave privada.*/
void printPrivateKey(Key key){

    PrivateKey* privateKey = (PrivateKey*) key;

    char* N = ui128toa(privateKey->N);
    char* d = ui128toa(privateKey->d);

    printf("Chave privada <%s,%s>\n", N, d);

    free(N);
    free(d);
}