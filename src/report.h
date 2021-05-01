#ifndef REPORT_H
#define REPORT_H

#include <stdio.h>

#include "rsa.h"
#include "ui128toa.h"
#include "types.h"

FILE* createReportFile(char* path);
void addReport(FILE* reportFile, int primeNum, Key publicKey, Key privateKey, long int M, ui128 cypher, long int decypheredM);

#endif