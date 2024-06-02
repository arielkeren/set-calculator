#include "globals.h"

/* Every possible operation name. */
const char *OPERATIONS[] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set", "stop"};
/* Every possible set name. */
const char *SETS[] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};
/* All the characters which should be ignored in the input line. */
const char SEPARATORS[] = ", \t\n";
