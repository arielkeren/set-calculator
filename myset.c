/*
 * myset.c
 * Includes the main function, which runs the program.
 *
 * Name: Ariel Keren
 * Course: C Lab, 20465
 * Semester: 2024B
 * Date: 07/06/2024
 */

#include "globals.h"
#include "mysetUtils.h"
#include "set.h"

/**
 * Initializes the 6 sets to be used in the program.
 * Prints an explanation of the program.
 * Runs the program.
 *
 * @return 0 when run successfully.
 */
int main() {
    /* The 6 sets used in the program. */
    set SETA, SETB, SETC, SETD, SETE, SETF;
    /* An array containing all the sets, so they can be passed more easily to functions. */
    setptr sets[NUMBER_OF_SETS];

    initializeSets(sets, SETA, SETB, SETC, SETD, SETE, SETF);

    /* Reset all the sets. */
    resetSets(sets);

    /* Print an explanation of the program, along with every valid command. */
    printExplanation();
    /* Start the program. */
    readInput(sets);

    /* Return 0 when run successfully. */
    return SUCCESS;
}
