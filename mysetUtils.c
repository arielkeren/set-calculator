#include "mysetUtils.h"

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

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
    printf("<number> is an integer in the range 0-127.\n");
}

/**
 * Resets all the sets in the given set array.
 * Sets every section of every set to 0.
 *
 * @param sets An array of sets.
 */
void resetSets(set sets[]) {
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
 * Runs the program.
 * First, reads a line as input from the user.
 * Second, checks if the line is valid.
 * Third, executes the input.
 * Repeats these steps until the end of the program.
 *
 * @param sets An array of sets.
 */
void readInput(set sets[]) {
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

        /* Skip to the next input if the line is invalid. */
        if (!isLineValid(line)) {
            continue;
        }

        /* Execute the user's command. */
        if (executeLine(line, sets)) {
            /* Stop the program if the command was stop. */
            isStopped = TRUE;
        }

        /* The input is no longer used. */
        free(line);
    }
}

/**
 * Reads and returns a line as input from the user.
 * Exits the program if an error occurs or if end of file is reached.
 *
 * @return The line as input from the user.
 */
char *readLine() {
    char *line;  /* Input line from the user. */
    size_t size; /* Size of the input line. */

    /* Exit the program if the end of file is reached. */
    checkEndOfFile();

    /* Allocate initial memory for the input line. */
    size = STARTING_LINE_LENGTH;
    line = malloc(size * sizeof(char));

    /* Check for an error in the memory allocation. */
    if (line == NULL) {
        /* Exit the program. */
        fprintf(stderr, "Failed to allocate memory for the input.\n");
        exit(ERROR);
    }

    /* Read the initial bit of the input line. */
    fgets(line, size, stdin);
    /* Exit the program if an error has occured. */
    checkFileError();

    /* Keep reading more of the input line until a newline character is present. */
    while (strchr(line, '\n') == NULL) {
        /* Increase the size of the input line. */
        size *= LINE_EXPANSION_FACTOR;
        /* Allocate more memory for the input line. */
        line = realloc(line, size * sizeof(char));

        /* Check for an error in the memory allocation. */
        if (line == NULL) {
            /* Exit the program. */
            fprintf(stderr, "Failed to allocate memory for the input.\n");
            exit(ERROR);
        }

        /* Read the next bit of the input line. */
        fgets(line, size, stdin);
        /* Exit the program if an error has occured. */
        checkFileError();
    }

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

/**
 * Exits the program if an error occurs in the standard input.
 */
void checkFileError() {
    /* Check for an error in the standard input. */
    if (ferror(stdin)) {
        /* Exit the program. */
        fprintf(stderr, "Failed to read the input.\n");
        exit(ERROR);
    }
}
