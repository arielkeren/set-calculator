#ifndef MYSET_UTILS_H
#define MYSET_UTILS_H

#include <stdio.h>

#include "globals.h"

void readInput(setptr sets[]);
void printExplanation();
void initializeSets(setptr sets[], set setA, set setB, set setC, set setD, set setE, set setF);
void resetSets(setptr sets[]);
char *readLine();
void checkEndOfFile();
void checkFileError();

#endif
