myset: myset.o mysetUtils.o utils.o set.o setUtils.o validation.o execution.o globals.o
	gcc -ansi -Wall -pedantic -o myset myset.o mysetUtils.o utils.o set.o setUtils.o validation.o execution.o globals.o

myset.o: myset.c mysetUtils.h globals.h set.h
	gcc -c -ansi -Wall -pedantic -o myset.o myset.c

mysetUtils.o: mysetUtils.c mysetUtils.h validation.h execution.h globals.h set.h
	gcc -c -ansi -Wall -pedantic -o mysetUtils.o mysetUtils.c

utils.o: utils.c utils.h globals.h
	gcc -c -ansi -Wall -pedantic -o utils.o utils.c

set.o: set.c set.h setUtils.h globals.h
	gcc -c -ansi -Wall -pedantic -o set.o set.c

setUtils.o: setUtils.c setUtils.h globals.h set.h
	gcc -c -ansi -Wall -pedantic -o setUtils.o setUtils.c

validation.o: validation.c validation.h utils.h globals.h
	gcc -c -ansi -Wall -pedantic -o validation.o validation.c

execution.o: execution.c execution.h set.h utils.h globals.h
	gcc -c -ansi -Wall -pedantic -o execution.o execution.c

globals.o: globals.c globals.h
	gcc -c -ansi -Wall -pedantic -o globals.o globals.c
