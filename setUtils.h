#ifndef SET_UTILS_H
#define SET_UTILS_H

#include "set.h"

/**
 * Checks if the given set is empty.
 *
 * @param setA The set to check.
 * @return TRUE if the set is empty, FALSE otherwise.
 */
boolean isSetEmpty(const set setA);

/**
 * Converts a non-empty set to its string representation and prints it.
 * Assumes the set is non-empty.
 * Every number is the set is separated by a comma and a space.
 * No more than 16 numbers shall occupy the same line.
 *
 * @param setA The set to print.
 */
void printSetAsString(const set setA);

#endif
