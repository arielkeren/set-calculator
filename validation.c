#include "validation.h"

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "utils.h"

boolean isLineValid(const char line[]) {
    char *lineCopy;
    char *token;
    boolean isValid;

    lineCopy = duplicateString(line);
    token = tokenizeLine(lineCopy);

    if (token == NULL) {
        return FALSE;
    }

    switch (getOperationIndex(token)) {
        case STOP:
            isValid = handleStop();
            break;
        case PRINT_SET:
            isValid = handlePrintSet();
            break;
        case READ_SET:
            isValid = handleReadSet();
            break;
        case INVALID_INDEX:
            fprintf(stderr, "Error: Invalid operation.\n");
            isValid = FALSE;
            break;
        default:
            isValid = handleSetOperation();
            break;
    }

    free(lineCopy);
    return isValid;
}

boolean handleStop() {
    if (getNextToken() != NULL) {
        fprintf(stderr, "Error: stop does not accept any operands.\n");
        return FALSE;
    }

    return TRUE;
}

boolean handlePrintSet() {
    if (getSetIndex(getNextToken()) == INVALID_INDEX) {
        fprintf(stderr, "Error: Invalid set name.\n");
        return FALSE;
    }

    if (getNextToken() != NULL) {
        fprintf(stderr, "Error: print_set only accepts a single operand.\n");
        return FALSE;
    }

    return TRUE;
}

boolean handleReadSet() {
    char *nextToken;
    char *token;

    token = getNextToken();

    if (!doesEndWithComma(token)) {
        fprintf(stderr, "Error: Missing comma.\n");
        return FALSE;
    }

    removeComma(token);

    if (getSetIndex(token) == -1) {
        fprintf(stderr, "Error: Invalid set name.\n");
        return FALSE;
    }

    token = getNextToken();
    nextToken = getNextToken();

    while (token != NULL) {
        if (nextToken != NULL && !doesEndWithComma(token)) {
            fprintf(stderr, "Error: Missing comma.\n");
            return FALSE;
        }

        removeComma(token);

        if (!isInteger(token)) {
            fprintf(stderr, "Error: Set members can be integers only.\n");
            return FALSE;
        }

        if (atoi(token) > LARGEST_MEMBER || (nextToken != NULL && atoi(token) < SMALLEST_MEMBER)) {
            fprintf(stderr, "Error: A set can only contain integers in the range 0-127.\n");
            return FALSE;
        }

        if (nextToken == NULL && atoi(token) != TERMINATOR) {
            fprintf(stderr, "Error: A read_set command should be terminated with a -1.\n");
            return FALSE;
        }

        token = nextToken;
        nextToken = getNextToken();
    }

    return TRUE;
}

boolean handleSetOperation() {
    char *nextToken;
    unsigned operandCount;
    char *token;

    token = getNextToken();
    operandCount = STARTING_VALUE;
    nextToken = getNextToken();

    while (token != NULL) {
        if (operandCount == SET_OPERATION_OPERANDS) {
            fprintf(stderr, "Error: Set operations only accept exactly 3 operands.\n");
            return FALSE;
        }

        if (nextToken != NULL && !doesEndWithComma(token)) {
            fprintf(stderr, "Error: Missing comma.\n");
            return FALSE;
        }

        removeComma(token);

        if (getSetIndex(token) == INVALID_INDEX) {
            fprintf(stderr, "Error: Invalid set name.\n");
            return FALSE;
        }

        token = nextToken;
        nextToken = getNextToken();
        operandCount++;
    }

    return TRUE;
}