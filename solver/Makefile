CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O2
CPPFLAGS =

LDFLAGS =
LDLIBS =

SRC = main.c sudoku.c read_file.c
OBJ = ${SRC:.c=.o}
EXEC = main

all : ${EXEC}
	@echo ${EXEC}

${EXEC} : ${OBJ}

clean :
	${RM} ${OBJ} ${EXEC}
