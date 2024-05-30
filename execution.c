#include "execution.h"

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "set.h"
#include "utils.h"

boolean executeLine(char line[], setptr sets[]) {
    boolean isStopped;
    char *lineCopy;

    lineCopy = duplicateString(line);
    isStopped = FALSE;

    switch (getOperationIndex(tokenizeLine(lineCopy))) {
        case STOP:
            isStopped = TRUE;
            break;
        case PRINT_SET:
            executePrintSet(line, sets);
            break;
        case READ_SET:
            executeReadSet(line, sets);
            break;
        default:
            executeSetOperation(line, sets);
            break;
    }

    free(lineCopy);
    return isStopped;
}

void executePrintSet(char line[], setptr sets[]) {
    char *lineCopy;

    lineCopy = duplicateString(line);
    tokenizeLine(lineCopy);
    print_set(getMatchingSet(getNextToken(), sets));

    free(lineCopy);
}

void executeReadSet(char line[], setptr sets[]) {
    operand *numbers;
    size_t length;
    size_t index;
    setptr setToFill;
    char *token;
    char *lineCopy;

    lineCopy = duplicateString(line);
    tokenizeLine(lineCopy);
    setToFill = getMatchingSet(getNextToken(), sets);

    while (getNextToken()) {
        length++;
    }

    free(lineCopy);

    numbers = malloc(length * sizeof(operand));

    if (numbers == NULL) {
        fprintf(stderr, "Failed to allocate memory for read_set's integer operands.\n");
        return;
    }

    lineCopy = duplicateString(line);
    tokenizeLine(lineCopy);
    getNextToken();

    for (index = FIRST_INDEX; index < length; index++) {
        token = getNextToken();
        numbers[index] = atoi(token);
    }

    free(lineCopy);
    read_set(setToFill, numbers);
    free(numbers);
}

void executeSetOperation(char line[], setptr sets[]) {
    int operationIndex;
    int index;
    char *lineCopy;
    setptr targetSets[SET_OPERATION_OPERANDS];

    lineCopy = duplicateString(line);
    operationIndex = getOperationIndex(tokenizeLine(lineCopy));

    for (index = FIRST_INDEX; index < SET_OPERATION_OPERANDS; index++) {
        targetSets[index] = getMatchingSet(getNextToken(), sets);
    }

    free(lineCopy);

    switch (operationIndex) {
        case UNION_SET:
            union_set(targetSets[FIRST_INDEX], targetSets[SECOND_INDEX], targetSets[THIRD_INDEX]);
            break;
        case INTERSECT_SET:
            intersect_set(targetSets[FIRST_INDEX], targetSets[SECOND_INDEX], targetSets[THIRD_INDEX]);
            break;
        case SUB_SET:
            sub_set(targetSets[FIRST_INDEX], targetSets[SECOND_INDEX], targetSets[THIRD_INDEX]);
            break;
        case SYMDIFF_SET:
            symdiff_set(targetSets[FIRST_INDEX], targetSets[SECOND_INDEX], targetSets[THIRD_INDEX]);
            break;
    }
}
