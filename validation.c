#include "validation.h"

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "utils.h"

/**
 * Checks if the given line represents a valid command.
 * Assumes the line is null-terminated.
 *
 * @param line The line to validate.
 * @return TRUE if the line is valid, FALSE otherwise.
 */
boolean isLineValid(const char line[]) {
    char *lineCopy;  /* A copy of the input line. */
    char *operation; /* The operation's name (e.g. "read_set"). */
    boolean isValid; /* Is the line valid? */

    /* Copy the input line to tokenize it. */
    lineCopy = duplicateString(line);
    /* Tokenize the line and get the first token (the operation). */
    operation = tokenizeLine(lineCopy);

    /* If the line is empty or if it consists only of whitespace, it should be skipped. */
    if (operation == NULL) {
        /* Skip this line without printing an error message. */
        return FALSE;
    }

    /* Separate the validation into different cases based on the operation. */
    switch (getOperationIndex(operation)) {
        case STOP:
            /* Handle stop. */
            isValid = validateStop();
            break;
        case PRINT_SET:
            /* Handle print_set. */
            isValid = validatePrintSet();
            break;
        case READ_SET:
            /* Handle read_set. */
            isValid = validateReadSet();
            break;
        case INVALID_INDEX:
            /* This means that the operation is invalid. */
            fprintf(stderr, "Error: Invalid operation.\n");
            isValid = FALSE;
            break;
        default:
            /* Handle union_set, intersect_set, sub_set or symdiff_set. */
            isValid = validateSetOperation();
            break;
    }

    /* The line copy is no longer used. */
    free(lineCopy);
    return isValid;
}

/**
 * Checks if the stop command is valid.
 * Gets the command via the tokenized line.
 *
 * @return TRUE if the command is valid, FALSE otherwise.
 */
boolean validateStop() {
    /* Check if there are any operands, which should not be there. */
    if (getNextToken() != NULL) {
        fprintf(stderr, "Error: stop does not accept any operands.\n");
        return FALSE;
    }

    return TRUE;
}

/**
 * Checks if the print_set command is valid.
 * Gets the command via the tokenized line.
 *
 * @return TRUE if the command is valid, FALSE otherwise.
 */
boolean validatePrintSet() {
    /* Check if there is an operand, which represents valid set. */
    if (getSetIndex(getNextToken()) == INVALID_INDEX) {
        fprintf(stderr, "Error: Invalid set name.\n");
        return FALSE;
    }

    /* Check if there any extra operands, which should not be there. */
    if (getNextToken() != NULL) {
        fprintf(stderr, "Error: print_set only accepts a single operand.\n");
        return FALSE;
    }

    return TRUE;
}

/**
 * Checks if the read_set command is valid.
 * Gets the command via the tokenized line.
 *
 * @return TRUE if the command is valid, FALSE otherwise.
 */
boolean validateReadSet() {
    char *token;       /* The current token. */
    char *nextToken;   /* The next token. */
    int numberOperand; /* The number operand, converted to */

    /* Get the (what should be) target set's name. */
    token = getNextToken();

    /* Check if there is a comma after the (supposed) set's name. */
    if (!doesEndWithComma(token)) {
        fprintf(stderr, "Error: Missing comma.\n");
        return FALSE;
    }

    /* Remove the comma. */
    removeComma(token);

    /* Check if there are some commas left after removing one. */
    if (doesEndWithComma(token)) {
        fprintf(stderr, "Error: Two or more consecutive commas.\n");
        return FALSE;
    }

    /* Check if the target set's name is valid. */
    if (getSetIndex(token) == INVALID_INDEX) {
        fprintf(stderr, "Error: Invalid set name.\n");
        return FALSE;
    }

    /* Get the first (supposed) number operand. */
    token = getNextToken();

    /* Check if there are any operands after the set's name. */
    if (token == NULL) {
        fprintf(stderr, "Error: A read_set command should include some numbers as operands.\n");
    }

    /* Get the operand after it to always know if the current operand is the last one (to check for a comma). */
    nextToken = getNextToken();

    /* Loops over all remaining operands. They should all be numbers. */
    while (token != NULL) {
        /* Check for a comma if the current operand is not the last one. */
        if (nextToken != NULL && !doesEndWithComma(token)) {
            fprintf(stderr, "Error: Missing comma.\n");
            return FALSE;
        }

        /* Check if there is a comma after the last operand. */
        if (nextToken == NULL && doesEndWithComma(token)) {
            fprintf(stderr, "Error: The last operand should not have a comma after it.\n");
            return FALSE;
        }

        /* Remove the comma if the current operand is not the last one. */
        if (nextToken != NULL) {
            removeComma(token);
        }

        /* Check if there are some commas left after removing one. */
        if (doesEndWithComma(token)) {
            fprintf(stderr, "Error: Two or more consecutive commas.\n");
            return FALSE;
        }

        /* Check if the operand is an integer. */
        if (!isInteger(token)) {
            fprintf(stderr, "Error: Set members should be integers only.\n");
            return FALSE;
        }

        /* Convert the operand to an integer. */
        numberOperand = atoi(token);

        /* Check if the operand is outside the valid range of integers. The last one should always be -1. */
        if (numberOperand > LARGEST_MEMBER || (nextToken != NULL && numberOperand < SMALLEST_MEMBER)) {
            fprintf(stderr, "Error: Set members should only be integers in the range 0-127.\n");
            return FALSE;
        }

        /* Check if the last operand is indeed a -1. */
        if (nextToken == NULL && numberOperand != TERMINATOR) {
            fprintf(stderr, "Error: A read_set command should be terminated with a -1.\n");
            return FALSE;
        }

        /* Move to the next operand to check. */
        token = nextToken;
        nextToken = getNextToken();
    }

    return TRUE;
}

/**
 * Checks if the union_set, intersect_set, sub_set or symdiff_set command is valid.
 * Gets the command via the tokenized line.
 *
 * @return TRUE if the command is valid, FALSE otherwise.
 */
boolean validateSetOperation() {
    char *token;              /* The current token. */
    char *nextToken;          /* The next token. */
    unsigned operandsChecked; /* The current number of operands checked. */

    /* Start counting from 0. */
    operandsChecked = STARTING_VALUE;
    /* Get the first operand. */
    token = getNextToken();
    /* Get the next operand to always know if the current operand is the last one (to check for a comma). */
    nextToken = getNextToken();

    /* Loops over all operands. */
    while (token != NULL) {
        /* Check if there are too many operands (more than the three sets needed). */
        if (operandsChecked == SET_OPERATION_OPERANDS) {
            fprintf(stderr, "Error: Set operations only accept exactly 3 operands.\n");
            return FALSE;
        }

        /* Check for a comma if the current operand is not the last one. */
        if (nextToken != NULL && !doesEndWithComma(token)) {
            fprintf(stderr, "Error: Missing comma.\n");
            return FALSE;
        }

        /* Check if there is a comma after the last operand. */
        if (nextToken == NULL && doesEndWithComma(token)) {
            fprintf(stderr, "Error: The last operand should not have a comma after it.\n");
            return FALSE;
        }

        /* Remove the comma if the current operand is not the last one. */
        if (nextToken != NULL) {
            removeComma(token);
        }

        /* Check if there are some commas left after removing one. */
        if (doesEndWithComma(token)) {
            fprintf(stderr, "Error: Two or more consecutive commas.\n");
            return FALSE;
        }

        /* Check if the operand is a valid set. */
        if (getSetIndex(token) == INVALID_INDEX) {
            fprintf(stderr, "Error: Invalid set name.\n");
            return FALSE;
        }

        /* Move to the next operand to check. */
        token = nextToken;
        nextToken = getNextToken();
        /* Increment the number of operands checked. */
        operandsChecked++;
    }

    return TRUE;
}