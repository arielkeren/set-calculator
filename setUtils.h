#ifndef SETUTILS_H
#define SETUTILS_H

#include "globals.h"

boolean isSetEmpty(const set setA);
char *setToString(const set setA);
size_t getSetStringLength(const set setA);
void fillSetString(const set setA, char string[]);

#endif
