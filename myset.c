#include "globals.h"
#include "mysetUtils.h"

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
    set sets[] = {SETA, SETB, SETC, SETD, SETE, SETF};

    /* Reset all the sets. */
    resetSets(sets);

    /* Print an explanation of the program, along with every valid command. */
    printExplanation();
    /* Start the program. */
    readInput(sets);

    /* Return 0 when run successfully. */
    return SUCCESS;
}
