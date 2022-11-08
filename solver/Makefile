CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O2
CPPFLAGS =

LDFLAGS =
LDLIBS =

SRC = main.c sudoku.c read_file.c
OBJ = ${SRC:.c=.o}
EXEC = solver

all : ${OBJ}
	${CC} ${OBJ} -o ${EXEC}

clean :
	${RM} ${OBJ}
	${RM} ${EXEC}
	${RM} *.swp

