/*
 * execution.h
 * Includes the prototypes of all the functions in execution.c.
 *
 * Name: Ariel Keren
 * Course: C Lab, 20465
 * Semester: 2024B
 * Date: 07/06/2024
 */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "set.h"

/**
 * Executes the input line, based on the operation and the operands.
 *
 * @param line The input line.
 * @param sets An array of sets.
 * @return TRUE if the program should be stopped, FALSE otherwise.
 */
boolean executeLine(char line[], setptr sets[]);

/**
 * Executes the print_set command.
 * Prints the set specified by the command.
 *
 * @param line The input line.
 * @param sets An array of sets.
 */
void executePrintSet(char line[], setptr sets[]);

/**
 * Executes the read_set command.
 * Fills the set with the given numbers, as specified by the command.
 *
 * @param line The input line.
 * @param sets An array of sets.
 */
void executeReadSet(char line[], setptr sets[]);

/**
 * Executes union_set, intersect_set, sub_set or symdiff_set.
 * Applies the operation to the sets, as specified by the command.
 *
 * @param line The input line.
 * @param sets An array of sets.
 */
void executeSetOperation(char line[], setptr sets[]);

#endif
