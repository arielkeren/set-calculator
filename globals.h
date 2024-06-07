/*
 * globals.h
 * Includes some global constants, types and enums for the program.
 *
 * Name: Ariel Keren
 * Course: C Lab, 20465
 * Semester: 2024B
 * Date: 07/06/2024
 */

#ifndef GLOBALS_H
#define GLOBALS_H

/* Exit codes. */
#define SUCCESS 0 /* The program has run successfully. */
#define ERROR 1   /* An error occurred. */

/* Set information. */
#define SET_SIZE 16        /* Number of sections in a set (128 / 8 = 16). */
#define SMALLEST_MEMBER 0  /* The smallest potential member in the set. */
#define LARGEST_MEMBER 127 /* The largest potential member in the set. */

/* Input line reading information. */
#define INITIAL_SIZE 256 /* The size of the starting string to read the input line into. */

/* Tokens and commas information. */
#define SINGLE_TOKEN 1             /* A single token in an input line (the number of commas should be 0). */
#define TOKENS_COMMAS_DIFFERENCE 2 /* The difference between the number of tokens and the number of commas in an input line. */

/* Command information. */
#define NUMBER_OF_OPERATIONS 7   /* The number of operations possible. */
#define NUMBER_OF_SETS 6         /* The number of sets possible. */
#define SET_OPERATION_OPERANDS 3 /* The number of operands needed for a set operation (e.g. union_set). */

/* Information for printing a set. */
#define NUMBERS_PER_LINE 16 /* The maximum number of set members in a single line when the set is printed. */

/* Information for bitwise operations.  */
#define SINGLE_BIT 1    /* A bit to use for a mask. */
#define BITS_PER_BYTE 8 /* The number of bits in a byte. */

/* Information for copying a string. */
#define NULL_BYTE 1 /* The extra byte to add when copying a string because of the null character. */

/* Information about indices. */
#define INVALID_INDEX (-1)      /* An invalid index (when searching for a set or an operation). */
#define NEXT_INDEX_DIFFERENCE 1 /* The difference between the current index and the next one. */

/* read_set. */
#define TERMINATOR (-1) /* The number which should terminate a read_set command. */

/* Extras. */
#define EMPTY 0          /* Used to check if something is empty (e.g. a set's section). */
#define STARTING_VALUE 0 /* Used to initialize variables for counting. */
#define NO_REMAINDER 0   /* Used to check if a number is divisible by some number. */

extern const char *OPERATIONS[]; /* All possible operation names (e.g. "print_set"). */
extern const char *SETS[];       /* All possible set names (e.g. "SETA"). */
extern const char SEPARATORS[];  /* All the characters which should be ignored in the input line. */

/* The type to loop over all sections in a set with. */
typedef unsigned char setindex;
/* The type consisting of all possible values of read_set's number operands. */
typedef signed char operand;

/* Boolean type. */
typedef enum { FALSE,
               TRUE } boolean;

/* An index for each possible operation. */
enum { READ_SET,
       PRINT_SET,
       UNION_SET,
       INTERSECT_SET,
       SUB_SET,
       SYMDIFF_SET,
       STOP };

/* An index for each possible set. */
enum { SETA_INDEX,
       SETB_INDEX,
       SETC_INDEX,
       SETD_INDEX,
       SETE_INDEX,
       SETF_INDEX };

/* The 6 first indices (used in loops and to populate arrays). */
enum { FIRST_INDEX,
       SECOND_INDEX,
       THIRD_INDEX,
       FOURTH_INDEX,
       FIFTH_INDEX,
       SIXTH_INDEX };

#endif
