# Set Calculator

Calculator for performing set operations.

## Background

This set calculator was one of the assignments for a course in C in The Open University of Israel.

## Features

### Overview

There are 6 sets to work with: SETA, SETB, SETC, SETD, SETE, SETF.<br>
Sets can be passed as operands, separated by commas, to the different commands of the calculator.<br>
Each set contains integers in the range 0-127 (including 0 and 127) in a very efficient way, allowing for fast operations and low memory usage.

### List of Commands

- `read_set <set> <value> <value> ... -1`<br>
  Reads values into the given set.<br>
  Gets a set to put the values in and a list of values, with -1 marking its end (the -1 is only a terminator, not to be put in the list).<br>
  **Note:** The set gets reset to being empty before putting any of the new values.
- `print_set <set>`<br>
  Prints the given set in a format where 16 values are displayed in each line.<br>
  If the set is empty, prints "The set is empty."
- `union_set <set> <set> <set>`
  Computes the union of the first 2 sets, and stores the result in the last set.<br>
  **Union** definition: A ∪ B = { x | x ∈ A or x ∈ B }
- `intersect_set <set> <set> <set>`
  Computes the intersection of the first 2 sets, and stores the result in the last set.<br>
  **Intersection** definition: A ∩ B = { x | x ∈ A and x ∈ B }
- `sub_set <set> <set> <set>`
  Computes the difference of the second set from the first set, and stores the result in the last set.<br>
  **Difference** definition: A \ B = { x | x ∈ A and x ∉ B }
- `symdiff_set <set> <set> <set>`
  Computes the symmetric difference of the first 2 sets, and stores the result in the last set.<br>
  **Symmetric difference** definition: A Δ B = (A \ B) ∪ (B \ A)

## Instructions
* Clone this repository.
  ```bash
  git clone https://github.com/arielkeren/set-calculator.git
  ```
* Run the Makefile.
  ```bash
  makefile
  ```
* Run the program.
  ```bash
  ./myset
  ```
