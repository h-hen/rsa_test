#include "ui128toa.h"

/*Inverte todos os caracteres de uma string.*/
static void strrev(char* str){
 
    int i, j;
    char ch;

    for(i = 0, j = strlen(str)-1; i<j; i++, j--){

        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
}

/*Converte um inteiro do tipo __uint128_t para uma string.*/
char* ui128toa(ui128 int128){

    char* str = (char*) calloc(40, sizeof(char));
    int i = 0;
    
    do{

        str[i++] = int128 % 10 + '0';

        int128 /= 10;
    
    } while (int128 > 0);

    char* buffer = realloc(str, sizeof(char)*i+1);

    if(buffer)
        str = buffer;

    strrev(str);

    return str;
}

/*Lê uma string do stdin, converte para um uint128.*/
ui128 scanui128(){

    char str[40];
    ui128 output = 0, power = 1;

    scanf(" %s", str);

    int strLen = strlen(str);

    for(int i = 0; i < strLen; i++){

        output = output + ((str[strLen - 1 - i] - '0') * power);
        power *= 10;
    }

    return output;
}