/*
 * set.h
 * Includes the prototypes of all the functions in set.c.
 * Also, includes some types for handling sets in the program.
 *
 * Name: Ariel Keren
 * Course: C Lab, 20465
 * Semester: 2024B
 * Date: 07/06/2024
 */

#ifndef SET_H
#define SET_H

#include "globals.h"

/* Each set section represents 8 numbers in the set. */
typedef unsigned char setsection;
/* A set is an array of 16 (128 numbers / 8 in each section) set sections. */
typedef setsection set[SET_SIZE];
/* Used as a pointer to a set when a set cannot be passed. */
typedef setsection *setptr;

/**
 * Reads the given numbers to the set (excluding the terminator).
 * Assumes the numbers array is terminated by -1.
 *
 * @param setA The set to fill.
 * @param numbers The numbers to add to the set.
 */
void read_set(set setA, const operand numbers[]);

/**
 * Converts and prints the given set's string representation.
 * If the set is empty, prints "The set is empty."
 * Otherwise, prints a string containing each element in the set.
 *
 * @param setA The set to print.
 */
void print_set(const set setA);

/**
 * Applies the union operation to set A and set B.
 * The result is every element in set A and/or in set B.
 * Stores the result in set C.
 *
 * @param setA The first set to apply the operation to.
 * @param setB The second set to apply the operation to.
 * @param setC The set to store the result in.
 */
void union_set(const set setA, const set setB, set setC);

/**
 * Applies the intersection operation to set A and set B.
 * The result is every element in set A, that is also in set B.
 * Stores the result in set C.
 *
 * @param setA The first set to apply the operation to.
 * @param setB The second set to apply the operation to.
 * @param setC The set to store the result in.
 */
void intersect_set(const set setA, const set setB, set setC);

/**
 * Applies the difference operation to set A and set B.
 * The result is every element in set A, that is not in set B.
 * Stores the result in set C.
 *
 * @param setA The first set to apply the operation to.
 * @param setB The second set to apply the operation to.
 * @param setC The set to store the result in.
 */
void sub_set(const set setA, const set setB, set setC);

/**
 * Applies the symmetric difference operation to set A and set B.
 * The result is every element only in one of the sets (not both).
 * Stores the result in set C.
 *
 * @param setA The first set to apply the operation to.
 * @param setB The second set to apply the operation to.
 * @param setC The set to store the result in.
 */
void symdiff_set(const set setA, const set setB, set setC);

#endif
