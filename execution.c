#include "execution.h"

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "set.h"
#include "utils.h"

/**
 * Executes the input line, based on the operation and the operands.
 *
 * @param line The input line.
 * @param sets An array of sets.
 * @return TRUE if the program should be stopped, FALSE otherwise.
 */
boolean executeLine(char line[], setptr sets[]) {
    boolean isStopped; /* Is the program stopped? */
    char *lineCopy;    /* A copy of the input line. */

    /* Copy the input line to tokenize it. */
    lineCopy = duplicateString(line);
    isStopped = FALSE;

    /* Determine the operation. */
    switch (getOperationIndex(tokenizeLine(lineCopy))) {
        case STOP:
            /* stop. */
            isStopped = TRUE;
            break;
        case PRINT_SET:
            /* print_set. */
            executePrintSet(line, sets);
            break;
        case READ_SET:
            /* read_set. */
            executeReadSet(line, sets);
            break;
        default:
            /* union_set, intersect_set, sub_set, symdiff_set. */
            executeSetOperation(line, sets);
            break;
    }

    /* The copy is no longer used. */
    free(lineCopy);
    /* Return whether to stop the program or not. */
    return isStopped;
}

/**
 * Executes the print_set command.
 * Prints the set specified by the command.
 *
 * @param line The input line.
 * @param sets An array of sets.
 */
void executePrintSet(char line[], setptr sets[]) {
    char *lineCopy; /* A copy of the input line. */

    /* Copy the input line to tokenize it. */
    lineCopy = duplicateString(line);
    tokenizeLine(lineCopy);
    /* Print the set. */
    print_set(getMatchingSet(getNextToken(), sets));

    /* The copy is no longer used. */
    free(lineCopy);
}

/**
 * Executes the read_set command.
 * Fills the set with the given numbers, as specified by the command.
 *
 * @param line The input line.
 * @param sets An array of sets.
 */
void executeReadSet(char line[], setptr sets[]) {
    operand *numbers; /* The numbers to fill the set with. */
    size_t length;    /* The length of the numbers array. */
    size_t index;     /* Current index in the numbers array. */
    setptr setToFill; /* The set to fill, specified in the input line. */
    char *lineCopy;   /* A copy of the input line. */

    /* Copy the input line to tokenize it. */
    lineCopy = duplicateString(line);
    tokenizeLine(lineCopy);
    /* Determine which set to fill. */
    setToFill = getMatchingSet(getNextToken(), sets);

    /* Count the number of operands. */
    while (getNextToken() != NULL) {
        length++;
    }

    /* Exhausted the copy. */
    free(lineCopy);

    /* Allocate enough memory for the numbers array. */
    numbers = malloc(length * sizeof(operand));

    /* Check for an error in the memory allocation. */
    if (numbers == NULL) {
        /* Exit the program. */
        fprintf(stderr, "Failed to allocate memory for read_set's integer operands.\n");
        exit(ERROR);
    }

    /* Make another copy of the input line. */
    lineCopy = duplicateString(line);
    /* Tokenize it again. */
    tokenizeLine(lineCopy);
    /* Skip the second token, which is the set name. */
    getNextToken();

    /* Loop over the numbers array and fill it. */
    for (index = FIRST_INDEX; index < length; index++) {
        /* Get the current number and convert it to an integer. */
        numbers[index] = atoi(getNextToken());
    }

    /* The copy is no longer used. */
    free(lineCopy);
    /* Fill the set. */
    read_set(setToFill, numbers);
    /* The numbers array is no longer needed. */
    free(numbers);
}

/**
 * Executes union_set, intersect_set, sub_set or symdiff_set.
 * Applies the operation to the sets, as specified by the command.
 *
 * @param line The input line.
 * @param sets An array of sets.
 */
void executeSetOperation(char line[], setptr sets[]) {
    int operationIndex;                        /* The index of the operation. */
    unsigned index;                            /* Current index in the target sets array.*/
    char *lineCopy;                            /* A copy of the input line.*/
    setptr targetSets[SET_OPERATION_OPERANDS]; /* The three target sets. */

    /* Copy the input line to tokenize it. */
    lineCopy = duplicateString(line);
    /* Tokenize the input line, and get the operation index. */
    operationIndex = getOperationIndex(tokenizeLine(lineCopy));

    /* Loop over the target sets and fill it with the set operands. */
    for (index = FIRST_INDEX; index < SET_OPERATION_OPERANDS; index++) {
        targetSets[index] = getMatchingSet(getNextToken(), sets);
    }

    /* The copy is no longer used. */
    free(lineCopy);

    /* Determine what operation to execute. */
    switch (operationIndex) {
        case UNION_SET:
            /* Apply the union operation to the first two sets and store the result in the third. */
            union_set(targetSets[FIRST_INDEX], targetSets[SECOND_INDEX], targetSets[THIRD_INDEX]);
            break;
        case INTERSECT_SET:
            /* Apply the intersection operation to the first two sets and store the result in the third. */
            intersect_set(targetSets[FIRST_INDEX], targetSets[SECOND_INDEX], targetSets[THIRD_INDEX]);
            break;
        case SUB_SET:
            /* Apply the difference operation to the first two sets and store the result in the third. */
            sub_set(targetSets[FIRST_INDEX], targetSets[SECOND_INDEX], targetSets[THIRD_INDEX]);
            break;
        case SYMDIFF_SET:
            /* Apply the symmetric difference operation to the first two sets and store the result in the third. */
            symdiff_set(targetSets[FIRST_INDEX], targetSets[SECOND_INDEX], targetSets[THIRD_INDEX]);
            break;
        default:
            /* Should not happen (if the line validation works well). */
            break;
    }
}
