/*
 * utils.c
 * Includes some general functions for the program.
 * Some of the functionality:
 * - Getting the next token from a tokenized line.
 * - Tokenization of lines.
 * - Getting the associated index of a set or an operation.
 * - Duplication of strings.
 * - Checking if a string can be interpreted as a decimal integer.
 *
 * Name: Ariel Keren
 * Course: C Lab, 20465
 * Semester: 2024B
 * Date: 07/06/2024
 */

#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

/**
 * Returns the next token from the last tokenized string.
 * The tokens are separated by whitespace characters and commas in the original string.
 *
 * @return The next token from the last tokenized string.
 */
char *getNextToken() {
    /* strtok remembers the last tokenized string, so use it to get the next token. */
    return strtok(NULL, SEPARATORS);
}

/**
 * Tokenizes a string and returns the first token.
 * The tokens are separated by whitespace characters and commas in the original string.
 * Assumes the string is null-terminated.
 *
 * @param line The line to tokenize.
 * @return The first token from the line.
 */
char *tokenizeLine(char line[]) {
    /* Use strtok to tokenize the given string by whitespace characters and commas. */
    return strtok(line, SEPARATORS);
}

/**
 * Returns the index of the operation in the given string.
 * If the string is not one of the valid operations, returns -1.
 * Assumes the string is null-terminated.
 *
 * @param string The string to check.
 * @return The index of the operation in the given string or -1 if not found.
 */
int getOperationIndex(const char string[]) {
    /* Use indexOf to find the index of the operation that is in the given string. */
    return indexOf(OPERATIONS, string, NUMBER_OF_OPERATIONS);
}

/**
 * Returns the index of the set in the given string.
 * If the string is not one of the valid sets, returns -1.
 * Assumes the string is null-terminated.
 *
 * @param string The string to check.
 * @return The index of the set in the given string or -1 if not found.
 */
int getSetIndex(const char string[]) {
    /* Use indexOf to find the index of the set that is in the given string. */
    return indexOf(SETS, string, NUMBER_OF_SETS);
}

/**
 * Returns the index of the given word in the given array of words.
 * If the word is not in the array, returns -1.
 * Assumes the word and each word in the words array are null-terminated.
 *
 * @param words The array of words.
 * @param word The word to search for.
 * @param length The length of the words array.
 * @return The index of the given word in the given array of words or -1 if not found.
 */
int indexOf(const char *words[], const char word[], int length) {
    int index; /* Current index in the words array. */

    if (word == NULL) {
        return INVALID_INDEX;
    }

    /* Loop over each word in the words array. */
    for (index = FIRST_INDEX; index < length; index++) {
        /* Check if the current word matches the given word. */
        if (!strcmp(words[index], word)) {
            /* Found. */
            return index;
        }
    }

    /* Not found. */
    return INVALID_INDEX;
}

/**
 * Duplicates the given string and returns the copy.
 * Users of this function must free the returned string.
 * Assumes the string is null-terminated.
 *
 * @param string The string to duplicate.
 * @return A copy of the given string.
 */
char *duplicateString(const char string[]) {
    char *copy; /* A copy of the given string. */

    /* Allocate enough memory to the string's copy. */
    copy = malloc(sizeof(char) * (strlen(string) + NULL_BYTE));

    /* Check for an error in the memory allocation. */
    if (copy == NULL) {
        /* Exit the program. */
        fprintf(stderr, "Error: Failed to allocate enough memory to duplicate the line.\n");
        exit(ERROR);
    }

    /* Copy the string to the copy. */
    strcpy(copy, string);
    return copy;
}

/**
 * Checks if the given string is a decimal integer.
 * Allows for + and - signs before the digits.
 * Does not allow for a decimal point.
 * Does not allow for decimal places (to the right of the decimal point).
 * Assumes the string is null-terminated.
 *
 * @param string The string to check.
 * @return TRUE if the string is a decimal integer, FALSE otherwise.
 */
boolean isInteger(const char string[]) {
    /* Check if the string is empty. */
    if (*string == '\0') {
        return FALSE;
    }

    /* Skip over the sign if there is one. */
    if (*string == '-' || *string == '+') {
        string++;
    }

    /* Check if the remaining characters are digits. */
    while (*string != '\0') {
        if (!isdigit(*string)) {
            return FALSE;
        }
        /* Move to the next character. */
        string++;
    }

    /* Passed every check - an integer. */
    return TRUE;
}
