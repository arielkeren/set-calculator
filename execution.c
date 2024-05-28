#include <stdlib.h>
#include <stdio.h>
#include "execution.h"
#include "set.h"
#include "utils.h"
#include "globals.h"

boolean executeLine(char line[], set setA, set setB, set setC, set setD, set setE, set setF) {
    boolean isStopped;
    char *lineCopy;

    lineCopy = duplicateString(line);
    isStopped = FALSE;

    switch (getOperationIndex(tokenizeLine(lineCopy))) {
        case STOP:
            isStopped = TRUE;
            break;
        case PRINT_SET:
            executePrintSet(line, setA, setB, setC, setD, setE, setF);
            break;
        case READ_SET:
            executeReadSet(line, setA, setB, setC, setD, setE, setF);
            break;
        default:
            executeSetOperation(line, setA, setB, setC, setD, setE, setF);
            break;
    }

    free(lineCopy);
    return isStopped;
}

void executePrintSet(char line[], set setA, set setB, set setC, set setD, set setE, set setF) {
    char *setString;
    char *lineCopy;

    lineCopy = duplicateString(line);
    tokenizeLine(lineCopy);
    setString = print_set(getMatchingSet(getNextToken(), &setA, &setB, &setC, &setD, &setE, &setF));
    printf("%s\n", setString);

    free(setString);
    free(lineCopy);
}

void executeReadSet(char line[], set setA, set setB, set setC, set setD, set setE, set setF) {
    operand *numbers;
    size_t length;
    size_t index;
    setptr setToFill;
    char *token;
    char *lineCopy;

    lineCopy = duplicateString(line);
    tokenizeLine(lineCopy);
    setToFill = getMatchingSet(getNextToken(), &setA, &setB, &setC, &setD, &setE, &setF);

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

void executeSetOperation(char line[], set setA, set setB, set setC, set setD, set setE, set setF) {
    int operationIndex;
    int index;
    char *lineCopy;
    setptr sets[SET_OPERATION_OPERANDS];

    lineCopy = duplicateString(line);
    operationIndex = getOperationIndex(tokenizeLine(lineCopy));

    for (index = FIRST_INDEX; index < SET_OPERATION_OPERANDS; index++) {
        sets[index] = getMatchingSet(getNextToken(), &setA, &setB, &setC, &setD, &setE, &setF);
    }

    free(lineCopy);

    switch (operationIndex) {
        case UNION_SET:
            union_set(sets[FIRST_INDEX], sets[SECOND_INDEX], sets[THIRD_INDEX]);
            break;
        case INTERSECT_SET:
            intersect_set(sets[FIRST_INDEX], sets[SECOND_INDEX], sets[THIRD_INDEX]);
            break;
        case SUB_SET:
            sub_set(sets[FIRST_INDEX], sets[SECOND_INDEX], sets[THIRD_INDEX]);
            break;
        case SYMDIFF_SET:
            symdiff_set(sets[FIRST_INDEX], sets[SECOND_INDEX], sets[THIRD_INDEX]);
            break;
    }
}
