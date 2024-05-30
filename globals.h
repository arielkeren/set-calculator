#ifndef GLOBALS_H
#define GLOBALS_H

#define SUCCESS 0
#define ERROR 1

#define SMALLEST_MEMBER 0
#define LARGEST_MEMBER 127

#define TRIPLES_INDEX 12
#define TRIPLES_MASK 32
#define DOUBLES_INDEX 1
#define DOUBLES_MASK 4

#define STARTING_LINE_LENGTH 256
#define LINE_EXPANSION_FACTOR 2

#define SIZE_MAX (size_t)(-1)
#define EMPTY 0
#define SET_SIZE 16
#define TERMINATOR (-1)
#define BITS_PER_BYTE 8
#define SINGLE_BIT 1
#define NULL_BYTE 1
#define STARTING_VALUE 0
#define NUMBERS_PER_LINE 16
#define NO_REMAINDER 0
#define NUMBER_OF_OPERATIONS 7
#define NUMBER_OF_SETS 6
#define INVALID_INDEX (-1)
#define LAST_INDEX_DIFFERENCE 1
#define SET_OPERATION_OPERANDS 3

typedef unsigned char setsection;
typedef setsection set[SET_SIZE];
typedef setsection *setptr;
typedef unsigned char setindex;
typedef signed char operand;
typedef enum { FALSE,
               TRUE } boolean;

extern const char *OPERATIONS[];
extern const char *SETS[];
extern const char WHITESPACE[];

enum { READ_SET,
       PRINT_SET,
       UNION_SET,
       INTERSECT_SET,
       SUB_SET,
       SYMDIFF_SET,
       STOP };
enum { SETA_INDEX,
       SETB_INDEX,
       SETC_INDEX,
       SETD_INDEX,
       SETE_INDEX,
       SETF_INDEX };
enum { FIRST_INDEX,
       SECOND_INDEX,
       THIRD_INDEX,
       FOURTH_INDEX,
       FIFTH_INDEX,
       SIXTH_INDEX };
enum { SINGLE_DIGIT = 1,
       DOUBLE_DIGIT,
       TRIPLE_DIGIT };

#endif
