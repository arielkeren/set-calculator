#ifndef VALIDATION_H
#define VALIDATION_H

#include <stddef.h>

#include "globals.h"

boolean isLineValid(const char line[]);
boolean validateStop();
boolean validatePrintSet();
boolean validateReadSet();
boolean validateSetOperation();
boolean validateCommas(const char line[]);
boolean commasMatchTokens(const char line[]);
void removeWhitespace(char string[]);

#endif
