#ifndef MYSET_UTILS_H
#define MYSET_UTILS_H

#include <stdio.h>

#include "globals.h"

/**
 * Runs the program.
 * First, reads a line as input from the user.
 * Second, checks if the line is valid.
 * Third, executes the input.
 * Repeats these steps until the end of the program.
 *
 * @param sets An array of sets.
 */
void readInput(setptr sets[]);

/**
 * Prints an explanation of the program.
 * Prints every valid command with its operands.
 */
void printExplanation();

/**
 * Initializes the array containing all the sets.
 *
 * @param sets An array of sets to populate.
 * @param setA The first set.
 * @param setB The second set.
 * @param setC The third set.
 * @param setD The fourth set.
 * @param setE The fifth set.
 * @param setF The sixth set.
 */
void initializeSets(setptr sets[], set setA, set setB, set setC, set setD, set setE, set setF);

/**
 * Resets all the sets in the given set array.
 * Sets every section of every set to 0.
 *
 * @param sets An array of sets.
 */
void resetSets(setptr sets[]);

/**
 * Reads and returns a line as input from the user.
 * Exits the program if an error occurs or if end of file is reached.
 *
 * @return The line as input from the user.
 */
char *readLine();

/**
 * Exits the program if end of file is reached in the standard input.
 */
void checkEndOfFile();

/**
 * Exits the program if an error occurs in the standard input.
 */
void checkFileError();

#endif
