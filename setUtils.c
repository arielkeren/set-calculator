/*
 * setUtils.c
 * Includes functions to be used in set.c, mainly for printing sets.
 *
 * Name: Ariel Keren
 * Course: C Lab, 20465
 * Semester: 2024B
 * Date: 07/06/2024
 */

#include "setUtils.h"

#include <stdio.h>

#include "globals.h"
#include "set.h"

/**
 * Checks if the given set is empty.
 *
 * @param setA The set to check.
 * @return TRUE if the set is empty, FALSE otherwise.
 */
boolean isSetEmpty(const set setA) {
    setindex index; /* Current index in the set. */

    /* Loop over all sections in the set. */
    for (index = FIRST_INDEX; index < SET_SIZE; index++) {
        /* Check if the current section is not empty. */
        if (setA[index] != EMPTY) {
            /* The set is definitely not empty. */
            return FALSE;
        }
    }

    /* All sections are empty, so the set is definitely empty. */
    return TRUE;
}

/**
 * Converts a non-empty set to its string representation and prints it.
 * Assumes the set is non-empty.
 * Every number is the set is separated by a comma and a space.
 * No more than 16 numbers shall occupy the same line.
 *
 * @param setA The set to print.
 */
void printSetAsString(const set setA) {
    setindex index;              /* Current index in the set. */
    setsection mask;             /* Current mask (used to get a specific number from a section). */
    unsigned char currentNumber; /* Current number of positions checked in the set. */
    unsigned char numbersFound;  /* Current number of numbers found in the set. */

    numbersFound = STARTING_VALUE;
    currentNumber = STARTING_VALUE;

    /* Print the opening curly brace of the set. */
    printf("{");

    /* Loop over all sections in the set. */
    for (index = FIRST_INDEX; index < SET_SIZE; index++) {
        /* Loop over all possible numbers in each section. */
        for (mask = SINGLE_BIT; mask != EMPTY; mask <<= SINGLE_BIT) {
            /* Check if the current number is not in the set. */
            if ((setA[index] & mask) == EMPTY) {
                /* Add the position and skip the number. */
                currentNumber++;
                continue;
            }

            /* Print a comma and a space after each number (excluding the last one). */
            if (numbersFound != STARTING_VALUE) {
                printf(", ");
            }

            /* Print the number. */
            printf("%d", currentNumber);

            /* A position has been checked and a number has been found. */
            currentNumber++;
            numbersFound++;

            /* Every 16 numbers in a single line, move to the next line by printing a newline character. */
            if (numbersFound % NUMBERS_PER_LINE == NO_REMAINDER) {
                printf("\n");
            }
        }
    }

    /* Print the closing curly brace of the set. */
    printf("}");

    /* Print an extra newline character when necessary. */
    if (numbersFound % NUMBERS_PER_LINE != NO_REMAINDER) {
        printf("\n");
    }
}
