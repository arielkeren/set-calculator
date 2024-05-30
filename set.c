#include "set.h"

#include "globals.h"
#include "setUtils.h"

/**
 * Reads the given numbers to the set (excluding the terminator).
 * Assumes the numbers array is terminated by -1.
 *
 * @param setA The set to fill.
 * @param numbers The numbers to add to the set.
 */
void read_set(set setA, const operand numbers[]) {
    setindex index;           /* Current index in the set. */
    setindex setPosition;     /* Current number's section index. */
    unsigned sectionPosition; /* Current number's position in its section. */

    /* Reset every section in the set. */
    for (index = FIRST_INDEX; index < SET_SIZE; index++) {
        setA[index] = EMPTY;
    }

    /* Add each number to the set. */
    for (index = FIRST_INDEX; numbers[index] != TERMINATOR; index++) {
        /* Find the number's section in the set. */
        setPosition = numbers[index] / (sizeof(setsection) * BITS_PER_BYTE);
        /* Find the number's position in its section. */
        sectionPosition = numbers[index] % (sizeof(setsection) * BITS_PER_BYTE);
        /* Shift a bit by the number's position in its section, then apply OR to the number's section. */
        setA[setPosition] |= SINGLE_BIT << sectionPosition;
    }
}

/**
 * Converts and prints the given set's string representation.
 * If the set is empty, prints "The set is empty."
 * Otherwise, prints a string containing each element in the set.
 *
 * @param setA The set to print.
 */
void print_set(const set setA) {
    /* Check if the set is empty. */
    if (isSetEmpty(setA)) {
        printf("The set is empty.");
        return;
    }

    /* Print the set's string representation. */
    printSetAsString(setA);
}

/**
 * Applies the union operation to set A and set B.
 * The result is every element in set A and/or in set B.
 * Stores the result in set C.
 *
 * @param setA The first set to apply the operation to.
 * @param setB The second set to apply the operation to.
 * @param setC The set to store the result in.
 */
void union_set(const set setA, const set setB, set setC) {
    setindex index; /* Current index in the set. */

    /* Apply OR to set A and set B's sections. Store in set C. */
    for (index = FIRST_INDEX; index < SET_SIZE; index++) {
        setC[index] = setA[index] | setB[index];
    }
}

/**
 * Applies the intersection operation to set A and set B.
 * The result is every element in set A, that is also in set B.
 * Stores the result in set C.
 *
 * @param setA The first set to apply the operation to.
 * @param setB The second set to apply the operation to.
 * @param setC The set to store the result in.
 */
void intersect_set(const set setA, const set setB, set setC) {
    setindex index; /* Current index in the set. */

    /* Apply AND to set A and set B's sections. Store in set C. */
    for (index = FIRST_INDEX; index < SET_SIZE; index++) {
        setC[index] = setA[index] & setB[index];
    }
}

/**
 * Applies the difference operation to set A and set B.
 * The result is every element in set A, that is not in set B.
 * Stores the result in set C.
 *
 * @param setA The first set to apply the operation to.
 * @param setB The second set to apply the operation to.
 * @param setC The set to store the result in.
 */
void sub_set(const set setA, const set setB, set setC) {
    setindex index; /* Current index in the set. */

    /* Apply AND to set A and set B's sections, after applying NOT to set B's sections. Store in set C. */
    for (index = FIRST_INDEX; index < SET_SIZE; index++) {
        setC[index] = setA[index] & ~setB[index];
    }
}

/**
 * Applies the symmetric difference operation to set A and set B.
 * The result is every element only in one of the sets (not both).
 * Stores the result in set C.
 *
 * @param setA The first set to apply the operation to.
 * @param setB The second set to apply the operation to.
 * @param setC The set to store the result in.
 */
void symdiff_set(const set setA, const set setB, set setC) {
    setindex index; /* Current index in the set. */

    /* Apply XOR to set A and set B's sections. Store in set C. */
    for (index = FIRST_INDEX; index < SET_SIZE; index++) {
        setC[index] = setA[index] ^ setB[index];
    }
}
