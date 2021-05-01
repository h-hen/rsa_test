#include "report.h"

FILE* createReportFile(char* path){

    FILE* report = fopen(path, "w+");

    if(report == NULL) return 0;

    fprintf(report, "n de primos, N, tamanho_N (bits), e, d, tamanho_d (bits), mensagem, cifra, msg_decifrada\n");

    return report;
}

void addReport(FILE* reportFile, int primeNum, Key publicKey, Key privateKey, long int M, ui128 cypher, long int decypheredM){

    ui128 N = getN(publicKey);
    ui128 d = getD(privateKey);
    unsigned int e = getE(publicKey);

    int size_N = (int) ceil(log2(N));
    int size_d = (int) ceil(log2(d));

    char* str_N = ui128toa(N);
    char* str_d = ui128toa(d);
    char* str_cypher = ui128toa(cypher);

    fprintf(reportFile, "%d, %s, %d, %u, %s, %d, %ld, %s, %ld\n", primeNum, str_N, size_N, e, str_d, size_d, M, str_cypher, decypheredM);

    free(str_N);
    free(str_d);
    free(str_cypher);
}