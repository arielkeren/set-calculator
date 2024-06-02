#include "validation.h"

#include <ctype.h>
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

    /* Validate every comma in the input line. */
    if (!validateCommas(line)) {
        free(lineCopy);
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
    int numberOperand; /* The current number operand, converted to an integer. */

    /* Check if the target set's name is valid. */
    if (getSetIndex(getNextToken()) == INVALID_INDEX) {
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
    char *token;                   /* The current token. */
    char *nextToken;               /* The next token. */
    unsigned char operandsChecked; /* The current number of operands checked. */

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

    /* Check if there too few operands. */
    if (operandsChecked < SET_OPERATION_OPERANDS) {
        fprintf(stderr, "Error: Set operations only accept exactly 3 operands.\n");
        return FALSE;
    }

    return TRUE;
}

/**
 * Checks if every comma in the given line is valid.
 * Assumes the line is null-terminated.
 *
 * @param line The line to validate the commas in.
 * @return TRUE if all of the commas in the line are valid, FALSE otherwise.
 */
boolean validateCommas(const char line[]) {
    char *lineCopy;      /* A copy of the input line. */
    char *current;       /* The current character. */
    boolean commaBefore; /* Whether a comma has been seen and there has not been a non-whitespace character after it. */
    boolean spaceSeen;   /* Whether a whitespace character has been seen. */

    commaBefore = FALSE;
    spaceSeen = FALSE;

    /* Copy the input line. */
    lineCopy = duplicateString(line);
    /* Remove all whitespace characters, except for the first one after the first token, from the copy. */
    removeWhitespace(lineCopy);

    /* Check if the first character is a comma. */
    if (*lineCopy == ',') {
        fprintf(stderr, "Error: Comma before the operation.\n");
        return FALSE;
    }

    /* Loops over all characters in the line. */
    for (current = lineCopy; *current != '\0'; current++) {
        /* Check for a comma. */
        if (*current == ',') {
            /* Check if there is a comma after the operation's name. */
            if (!spaceSeen) {
                fprintf(stderr, "Error: Comma after the operation.\n");
                free(lineCopy);
                return FALSE;
            }

            /* Check if there are two or more consecutive commas. */
            if (commaBefore) {
                fprintf(stderr, "Error: Two or more consecutive commas.\n");
                free(lineCopy);
                return FALSE;
            }

            /* Mark that a comma has been seen. */
            commaBefore = TRUE;
            continue;
        }

        /* Check for a whitespace character. */
        if (isspace(*current)) {
            /* Mark that a whitespace character has been seen. */
            spaceSeen = TRUE;

            /* Check if there is a comma after the space, that is after operation's name. */
            if (*(current + LAST_INDEX_DIFFERENCE) == ',') {
                fprintf(stderr, "Error: Comma after the operation.\n");
                free(lineCopy);
                return FALSE;
            }

            continue;
        }

        /* A non-whitespace character has been seen. */
        commaBefore = FALSE;
    }

    /* The line copy is no longer used. */
    free(lineCopy);

    /* Check if the last character is a comma. */
    if (commaBefore) {
        fprintf(stderr, "Error: Comma after the last operand.\n");
        return FALSE;
    }

    /* Check if there have been enough commas for the number of tokens. */
    if (!commasMatchTokens(line)) {
        fprintf(stderr, "Error: Missing comma.\n");
        return FALSE;
    }

    return TRUE;
}

/**
 * Checks if the number of commas in the given line fits the number of tokens in it.
 *
 * @param line The line to check.
 * @return TRUE if the number of commas fits the number of tokens, FALSE otherwise.
 */
boolean commasMatchTokens(const char line[]) {
    size_t commasFound; /* The number of commas found. */
    size_t tokensFound; /* The number of tokens (words separated by whitespace characters and commas) found. */
    boolean inToken;    /* Whether we are currently in a token. */

    inToken = FALSE;
    commasFound = STARTING_VALUE;
    tokensFound = STARTING_VALUE;

    /* Loop over all characters in the line. */
    while (*line != '\0') {
        if (isspace(*line)) {
            /* We are not in a token anymore. */
            inToken = FALSE;
        } else if (*line == ',') {
            /* We are not in a token anymore and a comma has been found. */
            inToken = FALSE;
            commasFound++;
        } else if (!inToken) {
            /* We are currently in a token. Count it. */
            inToken = TRUE;
            tokensFound++;
        }

        /* Move to the next character. */
        line++;
    }

    /* Generally, there should be two more tokens than commas, unless we are talking about a command consisting of a single token. */
    return tokensFound == SINGLE_TOKEN || commasFound + TOKENS_COMMAS_DIFFERENCE == tokensFound;
}

/**
 * Remove almost all whitespace characters from the given string.
 * Does not remove the first whitespace character after the first token.
 *
 * @param string The string to remove whitespace from.
 */
void removeWhitespace(char string[]) {
    char *current;         /* The current character. */
    char *insert;          /* The position to insert into. */
    boolean characterSeen; /* Whether a non-whitespace character has been seen. */
    boolean addedSpace;    /* Whether a whitespace character has already been added to the string. */

    characterSeen = FALSE;
    addedSpace = FALSE;

    /* Loop over all characters in the string. */
    for (current = insert = string; *current != '\0'; current++) {
        /* Determine whether the current character is a whitespace character. */
        if (isspace(*current)) {
            /* Add a single whitespace character if a non-whitespace character has been seen. */
            if (!addedSpace && characterSeen) {
                /* Insert the whitespace character. */
                *insert++ = *current;
                /* Mark that a whitespace character has been added. */
                addedSpace = TRUE;
            }
        } else {
            /* Insert the non-whitespace character. */
            *insert++ = *current;
            /* Mark that a non-whitespace character has been seen. */
            characterSeen = TRUE;
        }
    }

    /* Insert the terminating null character. */
    *insert = '\0';
}
