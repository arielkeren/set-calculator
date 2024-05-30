#ifndef UTILS_H
#define UTILS_H

#include "globals.h"

char *getNextToken();
char *tokenizeLine(char line[]);
int getOperationIndex(const char string[]);
int getSetIndex(const char string[]);
int indexOf(const char *words[], const char word[], int length);
char *duplicateString(const char string[]);
void removeComma(char string[]);
boolean doesEndWithComma(const char string[]);
boolean isInteger(const char string[]);
setptr getMatchingSet(char string[], setptr sets[]);

#endif
