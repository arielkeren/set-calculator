/*
 * globals.c
 * Includes some global constants for the program.
 *
 * Name: Ariel Keren
 * Course: C Lab, 20465
 * Semester: 2024B
 * Date: 07/06/2024
 */

#include "globals.h"

/* Every possible operation name. */
const char *OPERATIONS[] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set", "stop"};
/* Every possible set name. */
const char *SETS[] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};
/* All the characters which should be ignored in the input line. */
const char SEPARATORS[] = ", \t\n";
