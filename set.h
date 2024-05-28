#ifndef SET_H
#define SET_H

#include "globals.h"

void read_set(set setA, const operand numbers[]);
char *print_set(const set setA);
void union_set(const set setA, const set setB, set setC);
void intersect_set(const set setA, const set setB, set setC);
void sub_set(const set setA, const set setB, set setC);
void symdiff_set(const set setA, const set setB, set setC);

#endif
