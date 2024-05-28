#ifndef EXECUTION_H
#define EXECUTION_H

#include "globals.h"

boolean executeLine(char line[], set setA, set setB, set setC, set setD, set setE, set setF);
void executePrintSet(char line[], set setA, set setB, set setC, set setD, set setE, set setF);
void executeReadSet(char line[], set setA, set setB, set setC, set setD, set setE, set setF);
void executeSetOperation(char line[], set setA, set setB, set setC, set setD, set setE, set setF);

#endif
