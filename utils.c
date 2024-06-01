#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

/**
 * Returns the next token from the last tokenized string.
 * The tokens are separated by whitespace in the original string.
 *
 * @return The next token from the last tokenized string.
 */
char *getNextToken() {
    return strtok(NULL, WHITESPACE);
}

/**
 * Tokenizes a string and returns the first token.
 * The tokens are separated by whitespace in the original string.
 * Assumes the string is null-terminated.
 *
 * @param line The line to tokenize.
 * @return The first token from the line.
 */
char *tokenizeLine(char line[]) {
    return strtok(line, WHITESPACE);
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
    int index;

    for (index = FIRST_INDEX; index < length; index++) {
        if (!strcmp(words[index], word)) {
            return index;
        }
    }

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
    char *duplicate = malloc(sizeof(char) * (strlen(string) + NULL_BYTE));

    if (duplicate == NULL) {
        fprintf(stderr, "Error: Failed to allocate enough memory to duplicate the line.\n");
        exit(ERROR);
    }

    strcpy(duplicate, string);
    return duplicate;
}

/**
 * Removes a comma from the end of the given string if it exists.
 * Assumes the string is null-terminated.
 *
 * @param string The string to remove the comma from.
 */
void removeComma(char string[]) {
    if (doesEndWithComma(string)) {
        string[strlen(string) - LAST_INDEX_DIFFERENCE] = '\0';
    }
}

/**
 * Checks if the given string ends with a comma.
 * Assumes the string is null-terminated.
 *
 * @param string The string to check.
 * @return TRUE if the string ends with a comma, FALSE otherwise.
 */
boolean doesEndWithComma(const char string[]) {
    return string[strlen(string) - LAST_INDEX_DIFFERENCE] == ',';
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

/**
 * Returns the matching set for the given string, taken from the given sets array.
 * Removes the ending comma from the string if it exists.
 * Assumes the string is null-terminated.
 *
 * @param string The string to check.
 * @param sets An array of sets.
 * @return The matching set for the given string or NULL if not found.
 */
setptr getMatchingSet(char string[], setptr sets[]) {
    int index;

    removeComma(string);
    index = getSetIndex(string);

    return index == INVALID_INDEX ? NULL : sets[index];
}
