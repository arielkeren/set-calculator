#include "setUtils.h"

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

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
 * Converts a non-empty set to its string representation.
 * Assumes the set is not empty.
 * Every number is the set is separated by a comma and a space.
 * No more than 16 numbers shall be in the same line.
 *
 * @param setA The set to convert.
 * @return The set's string representation.
 */
char *setToString(const set setA) {
    char *string;  /* The set's string representation. */
    size_t length; /* The length of the set's string representation. */

    /* Determine the length of the set's string representation. */
    length = getSetStringLength(setA);
    /* Allocate enough memory for the set's string representation. */
    string = malloc(length * sizeof(char));

    /* Check for an error in the memory allocation. */
    if (string == NULL) {
        /* Exit the program. */
        fprintf(stderr, "Error: Failed to allocate enough memory for the set's string representation.\n");
        exit(ERROR);
    }

    /* Fill the set's string representation. */
    fillSetString(setA, string);

    return string;
}

/**
 * Computes and returns the length of the given set's string representation.
 * Assumes the set is not empty.
 *
 * @param setA The set to convert.
 * @return The length of the set's string representation.
 */
size_t getSetStringLength(const set setA) {
    setindex index;             /* Current index in the set. */
    size_t length;              /* Current length of the string. */
    unsigned char mask;         /* Current mask (used to get a specific number from a section). */
    unsigned char numbersFound; /* Current number of numbers found in the set. */

    length = NULL_BYTE;            /* Initialize the length to 1 to account for the ending null character. */
    numbersFound = STARTING_VALUE; /* Start counting the numbers from 0. */

    /* Loop over all sections in the set. */
    for (index = FIRST_INDEX; index < SET_SIZE; index++) {
        /* Loop over all possible numbers in each section. */
        for (mask = SINGLE_BIT; mask != EMPTY; mask <<= SINGLE_BIT) {
            /* Check if the current number is not in the set. */
            if ((setA[index] & mask) == EMPTY) {
                /* Skip it. */
                continue;
            }

            /* Numbers can be 0-127 in the set, so each one can be 1-3 digits long. */
            if (index > TRIPLES_INDEX || (index == TRIPLES_INDEX && mask >= TRIPLES_MASK)) {
                /*
                 * Index is 13+ => number is 104+ => number is 3 digits long.
                 * Index is 12 => number is between 96 and 103 => number is 2 or 3 digits long.
                 * Mask is 32+ (100000+ in binary) and index is 12 => number is between 96+4 and 103 => number is 3 digits long.
                 */
                length += TRIPLE_DIGIT;
            } else if (index > DOUBLES_INDEX || (index == DOUBLES_INDEX && mask >= DOUBLES_MASK)) {
                /*
                 * (The number is definitely not 3 digits long.)
                 * Index is 2+ => number is 16+ => number is 2 digits long.
                 * Index is 1 => number is between 8 and 15 => number is 1 or 2 digits long.
                 * Mask is 4+ (100+ in binary) and index is 1 => number is between 8+2 and 15 => number is 2 digits long.
                 */
                length += DOUBLE_DIGIT;
            } else {
                /* The number is definitely not 3 digits long, nor 2 digits long, so it is 1 digit long. */
                length += SINGLE_DIGIT;
            }

            /* Add a comma and a space between each number in the set. */
            length += COMMA_SPACE;
            /* A number has been found. */
            numbersFound++;

            /* Every 16 numbers in a single line, move to the next line by adding a newline. */
            if (numbersFound % NUMBERS_PER_LINE == NO_REMAINDER) {
                length += NEWLINE;
            }
        }
    }

    return length;
}

/**
 * Fills the given string with the string representation of the given set.
 * Assumes the set is not empty.
 * Assumes the string is large enough to hold the set's string representation.
 *
 * @param setA The set to convert.
 * @param string The string to store the set's string representation in.
 */
void fillSetString(const set setA, char string[]) {
    setindex index;              /* Current index in the set. */
    size_t stringIndex;          /* Current position in the string. */
    unsigned char currentNumber; /* Current number of positions checked in the set. */
    setsection mask;             /* Current mask (used to get a specific number from a section). */
    unsigned char numbersFound;  /* Current number of numbers found in the set. */

    /* Start counting from 0. */
    numbersFound = STARTING_VALUE;
    currentNumber = STARTING_VALUE;
    /* Start at the beginning of the string. */
    stringIndex = FIRST_INDEX;

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

            /* Separate the cases to 1-3 digits. In each one, append each digit of the number to the string. */
            if (index > TRIPLES_INDEX || (index == TRIPLES_INDEX && mask >= TRIPLES_MASK)) {
                string[stringIndex++] = '0' + currentNumber / 100;       /* Get the hundreds digit. */
                string[stringIndex++] = '0' + (currentNumber / 10) % 10; /* Get the tens digit. */
                string[stringIndex++] = '0' + currentNumber % 10;        /* Get the ones digit. */
            } else if (index > DOUBLES_INDEX || (index == DOUBLES_INDEX && mask >= DOUBLES_MASK)) {
                string[stringIndex++] = '0' + currentNumber / 10; /* Get the tens digit. */
                string[stringIndex++] = '0' + currentNumber % 10; /* Get the ones digit. */
            } else {
                string[stringIndex++] = '0' + currentNumber; /* Get the only digit in the number. */
            }

            /* Add a comma and a space between each number in the set. */
            string[stringIndex++] = ',';
            string[stringIndex++] = ' ';

            /* A position has been checked and a number has been found. */
            currentNumber++;
            numbersFound++;

            /* Every 16 numbers in a single line, move to the next line by appending a newline character. */
            if (numbersFound % NUMBERS_PER_LINE == NO_REMAINDER) {
                string[stringIndex++] = '\n';
            }
        }
    }

    /* Make sure the string is terminated with a null character. */
    string[stringIndex] = '\0';
}
