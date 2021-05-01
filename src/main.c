#include "primes.h"
#include "rsa.h"
#include "report.h"

int main(){

    FILE* reportFile;
    Prime* primes;
    Key publicKey, privateKey;
    ui128 o, p;

    int m, n;
    char ch, collectData;

    printf("Deseja coletar dados (S/N)?: ");
    scanf(" %c", &collectData);

    if(collectData == 'S' || collectData == 's')                                
        reportFile = createReportFile("report.csv");                          //Gerar arquivo de relatório

    srand(time(NULL));                                                          //Semear rand

    for(;;){                                                                    //Exec loop

        printf("Escolha o numero de primos (0 para encerrar o programa): ");
        scanf(" %d", &n);

        if(n == 0) break;

        printf("Deseja inserir uma chave? (S/N): ");
        scanf(" %c", &ch);

        printf("\nMensagem para criptografar: ");
        scanf(" %d", &m);

        primes = getPrimes(n);

        for(int i = 0; i < n; i++)
            printf("Primo %d: %u\n", i+1, primes[i]);

        if(ch == 'S' || ch == 's'){

            ui128 N, d;
            unsigned int e;

            printf("Insira N: ");
            N = scanui128();

            printf("Insira e: ");
            scanf(" %u", &e);
            
            publicKey = insertPublicKey(N, e);
            
            printf("Insira d: ");
            d = scanui128();

            privateKey = insertPrivateKey(N, d);

        }
        else{

            publicKey = getPublicKey(primes, n);

            privateKey = getPrivateKey(primes, n, getN(publicKey), getE(publicKey));
        }

        printPublicKey(publicKey);

        printPrivateKey(privateKey);

        o = encrypt(publicKey, m);
        char* strO = ui128toa(o);

        printf("\nCifra: %s\n", strO);

        if(ch == 'S' || ch == 's')
            p = simpleDecrypt(privateKey, o);
        else
            p = decrypt(privateKey, primes, n, o);

        char* strP = ui128toa(p);

        printf("Cifra decodificada: %s\n", strP);
        printf("\n==========================================================\n");

        if(collectData == 'S' || collectData == 's')
            addReport(reportFile, n, publicKey, privateKey, m, o, p);

        free(primes);                                                           //Liberação de memória
        free(publicKey);
        free(privateKey);
        free(strO);
        free(strP);
    }

    if(collectData == 'S' || collectData == 's')
        fclose(reportFile);

    return 0;
}