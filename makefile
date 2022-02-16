Pre-assembler: list.o Pre-assembler.o file_input.o
	gcc -g -Wall -ansi -pedantic list.o Pre-assembler.o file_input.o -o pre -lm
list.o: list.c Pre-assembler.h
	gcc -c -Wall -ansi -pedantic list.c -o list.o -lm 
file_input.o: file_input.c Pre-assembler.h
	gcc -c -Wall -ansi -pedantic file_input.c -o file_input.o
Pre-assembler.o: Pre-assembler.c Pre-assembler.h
	gcc -c -Wall -ansi -pedantic Pre-assembler.c -o Pre-assembler.o
clean: rm *~