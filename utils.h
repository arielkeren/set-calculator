/*
 * utils.h
 * Includes the prototypes of all the functions in utils.c.
 *
 * Name: Ariel Keren
 * Course: C Lab, 20465
 * Semester: 2024B
 * Date: 07/06/2024
 */

#ifndef UTILS_H
#define UTILS_H

#include "globals.h"

/**
 * Returns the next token from the last tokenized string.
 * The tokens are separated by whitespace characters and commas in the original string.
 *
 * @return The next token from the last tokenized string.
 */
char *getNextToken();

/**
 * Tokenizes a string and returns the first token.
 * The tokens are separated by whitespace characters and commas in the original string.
 * Assumes the string is null-terminated.
 *
 * @param line The line to tokenize.
 * @return The first token from the line.
 */
char *tokenizeLine(char line[]);

/**
 * Returns the index of the operation in the given string.
 * If the string is not one of the valid operations, returns -1.
 * Assumes the string is null-terminated.
 *
 * @param string The string to check.
 * @return The index of the operation in the given string or -1 if not found.
 */
int getOperationIndex(const char string[]);

/**
 * Returns the index of the set in the given string.
 * If the string is not one of the valid sets, returns -1.
 * Assumes the string is null-terminated.
 *
 * @param string The string to check.
 * @return The index of the set in the given string or -1 if not found.
 */
int getSetIndex(const char string[]);

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
int indexOf(const char *words[], const char word[], int length);

/**
 * Duplicates the given string and returns the copy.
 * Users of this function must free the returned string.
 * Assumes the string is null-terminated.
 *
 * @param string The string to duplicate.
 * @return A copy of the given string.
 */
char *duplicateString(const char string[]);

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
boolean isInteger(const char string[]);

#endif
