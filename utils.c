#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "globals.h"

char *getNextToken() {
    return strtok(NULL, WHITESPACE);
}

char *tokenizeLine(char line[]) {
    return strtok(line, WHITESPACE);
}

int getOperationIndex(const char string[]) {
    return indexOf(OPERATIONS, string, NUMBER_OF_OPERATIONS);
}

int getSetIndex(const char string[]) {
    return indexOf(SETS, string, NUMBER_OF_SETS);
}

int indexOf(const char *words[], const char word[], size_t length) {
    size_t index;

    for (index = FIRST_INDEX; index < length; index++) {
        if (!strcmp(words[index], word)) {
            return index;
        }
    }

    return INVALID_INDEX;
}

char *duplicateString(const char string[]) {
    char *duplicate = malloc(sizeof(char) * (strlen(string) + NULL_BYTE));

    if (duplicate == NULL) {
        fprintf(stderr, "Error: Failed to allocate enough memory to duplicate the line.\n");
        exit(ERROR);
    }

    strcpy(duplicate, string);
    return duplicate;
}

void removeComma(char string[]) {
    if (doesEndWithComma(string)) {
        string[strlen(string) - LAST_INDEX_DIFFERENCE] = '\0';
    }
}

boolean doesEndWithComma(const char string[]) {
    return string[strlen(string) - LAST_INDEX_DIFFERENCE] == ',';
}

boolean isInteger(const char string[]) {
    if (*string == '\0') {
        return FALSE;
    }

    if (*string == '-' || *string == '+') {
        string++;
    }

    while (*string != '\0') {
        if (!isdigit(*string)) {
            return FALSE;
        }
        string++;
    }

    return TRUE;
}

setptr getMatchingSet(char string[], setptr *setA, setptr *setB, setptr *setC, setptr *setD, setptr *setE, setptr *setF) {
    removeComma(string);

    switch (getSetIndex(string)) {
        case SETA_INDEX:
            return *setA;
        case SETB_INDEX:
            return *setB;
        case SETC_INDEX:
            return *setC;
        case SETD_INDEX:
            return *setD;
        case SETE_INDEX:
            return *setE;
        case SETF_INDEX:
            return *setF;
    }

    return NULL;
}
