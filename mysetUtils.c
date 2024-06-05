#include "mysetUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "execution.h"
#include "globals.h"
#include "set.h"
#include "utils.h"
#include "validation.h"

/**
 * Runs the program.
 * First, reads a line as input from the user.
 * Second, checks if the line is valid.
 * Third, executes the input.
 * Repeats these steps until the end of the program.
 *
 * @param sets An array of sets.
 */
void readInput(setptr sets[]) {
    boolean isStopped; /* Is the program stopped? */
    char *line;        /* Current line as input from the user. */

    isStopped = FALSE;

    /* Loop until the program is stopped. */
    while (!isStopped) {
        printf("\nPlease enter a command:\n");

        /* Read the command from the user. */
        line = readLine();

        /* Print the line that was entered. */
        printf("Your input: %s\n", line);

        /* Skip to the next input line if the current line is invalid. */
        if (!isLineValid(line)) {
            continue;
        }

        /* Execute the user's command. */
        if (executeLine(line, sets)) {
            /* Stop the program if the command was stop. */
            isStopped = TRUE;
        }

        /* The input line is no longer used. */
        free(line);

        printf("Command executed successfully!\n");
    }

    printf("Goodbye!\n");
}

/**
 * Prints an explanation of the program.
 * Prints every valid command with its operands.
 */
void printExplanation() {
    /* Explanation. */
    printf("Welcome! This program is a set calculator.\n");

    /* Valid commands. */
    printf("These are the possible commands:\n");
    printf("\nread_set <set>, <number>, <number>, ..., -1 --- Fills the set with the given numbers.\n");
    printf("print_set <set> --- Prints the set.\n");
    printf("union_set <set>, <set>, <set> --- Sets the third set to the union of the first two sets.\n");
    printf("intersect_set <set>, <set>, <set> --- Sets the third set to the intersection of the first two sets.\n");
    printf("sub_set <set>, <set>, <set> --- Sets the third set to the difference of the first two sets.\n");
    printf("symdiff_set <set>, <set>, <set> --- Sets the third set to the symmetric difference of the first two sets.\n");
    printf("stop --- Ends the program.\n");

    /* Valid operands. */
    printf("\nIn all commands:\n");
    printf("\n<set> is one of SETA, SETB, SETC, SETD, SETE, SETF.\n");
    printf("<number> is an integer in the range 0-127.\n\n");
}

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
void initializeSets(setptr sets[], set setA, set setB, set setC, set setD, set setE, set setF) {
    /* Populate each position in the array with the right set. */
    sets[FIRST_INDEX] = setA;
    sets[SECOND_INDEX] = setB;
    sets[THIRD_INDEX] = setC;
    sets[FOURTH_INDEX] = setD;
    sets[FIFTH_INDEX] = setE;
    sets[SIXTH_INDEX] = setF;
}

/**
 * Resets all the sets in the given set array.
 * Sets every section of every set to 0.
 *
 * @param sets An array of sets.
 */
void resetSets(setptr sets[]) {
    size_t index;             /* Current index in the set array. */
    setindex currentSetIndex; /* Current index of the set. */

    /* Loop over each set. */
    for (index = FIRST_INDEX; index < NUMBER_OF_SETS; index++) {
        /* Loop over each section of the set. */
        for (currentSetIndex = FIRST_INDEX; currentSetIndex < SET_SIZE; currentSetIndex++) {
            /* Reset the current section. */
            sets[index][currentSetIndex] = EMPTY;
        }
    }
}

/**
 * Reads and returns a line as input from the user.
 * Exits the program if an error occurs or if end of file is reached.
 *
 * @return The line as input from the user.
 */
char *readLine() {
    int character;  /* Current character of the input line. */
    char *line;     /* Input line from the user. */
    char *lastLine; /* The last input line. */
    size_t index;   /* Size of the input line. */

    /* Exit the program if the end of file is reached. */
    checkEndOfFile();
    index = FIRST_INDEX;

    /* Loop over the characters until the end of the line or the file. */
    while ((character = getchar()) != '\n' && character != EOF) {
        /* Allocate more memory if necessary. */
        if (index % INITIAL_SIZE == NO_REMAINDER) {
            /* Keep the pointer to the last line. */
            lastLine = line;
            /* Allocate more memory for the new line. */
            line = malloc((index + INITIAL_SIZE) * sizeof(char));

            /* Check for an error in the memory allocation. */
            if (line == NULL) {
                /* Exit the program. */
                fprintf(stderr, "Failed to allocate memory for the input.\n");
                exit(ERROR);
            }

            /* Copy the last line to the new line (if it is not the first time). */
            if (lastLine != NULL) {
                strcpy(line, lastLine);
                /* The last line is no longer used. */
                free(lastLine);
            }
        }

        /* Insert the current character and increment the index. */
        line[index++] = character;
    }

    /* Insert the terminating null character. */
    line[index] = '\0';
    /* Return the whole input line as it has been read. */
    return line;
}

/**
 * Exits the program if end of file is reached in the standard input.
 */
void checkEndOfFile() {
    /* Check for end of file in the standard input. */
    if (feof(stdin)) {
        /* Exit the program. */
        fprintf(stderr, "Error: Missing stop command.\n");
        exit(ERROR);
    }
}
