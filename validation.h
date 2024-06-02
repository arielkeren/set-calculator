#ifndef VALIDATION_H
#define VALIDATION_H

#include <stddef.h>

#include "globals.h"

/**
 * Checks if the given line represents a valid command.
 * Assumes the line is null-terminated.
 *
 * @param line The line to validate.
 * @return TRUE if the line is valid, FALSE otherwise.
 */
boolean isLineValid(const char line[]);

/**
 * Checks if the stop command is valid.
 * Gets the command via the tokenized line.
 *
 * @return TRUE if the command is valid, FALSE otherwise.
 */
boolean validateStop();

/**
 * Checks if the print_set command is valid.
 * Gets the command via the tokenized line.
 *
 * @return TRUE if the command is valid, FALSE otherwise.
 */
boolean validatePrintSet();

/**
 * Checks if the read_set command is valid.
 * Gets the command via the tokenized line.
 *
 * @return TRUE if the command is valid, FALSE otherwise.
 */
boolean validateReadSet();

/**
 * Checks if the union_set, intersect_set, sub_set or symdiff_set command is valid.
 * Gets the command via the tokenized line.
 *
 * @return TRUE if the command is valid, FALSE otherwise.
 */
boolean validateSetOperation();

/**
 * Checks if every comma in the given line is valid.
 * Assumes the line is null-terminated.
 *
 * @param line The line to validate the commas in.
 * @return TRUE if all of the commas in the line are valid, FALSE otherwise.
 */
boolean validateCommas(const char line[]);

/**
 * Checks if the number of commas in the given line fits the number of tokens in it.
 *
 * @param line The line to check.
 * @return TRUE if the number of commas fits the number of tokens, FALSE otherwise.
 */
boolean commasMatchTokens(const char line[]);

/**
 * Removes almost all whitespace characters from the given string.
 * Does not remove the first whitespace character after the first token.
 *
 * @param string The string to remove whitespace characters from.
 */
void removeWhitespace(char string[]);

#endif
