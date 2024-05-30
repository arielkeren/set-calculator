#ifndef EXECUTION_H
#define EXECUTION_H

#include "globals.h"

boolean executeLine(char line[], setptr sets[]);
void executePrintSet(char line[], setptr sets[]);
void executeReadSet(char line[], setptr sets[]);
void executeSetOperation(char line[], setptr sets[]);

#endif
