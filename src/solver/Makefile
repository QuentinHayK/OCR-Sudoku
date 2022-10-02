CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O2

SRC = main.c read_file.c
OBJ = {SRC:.c=.o}
EXEC = main

all : ${EXEC}

${EXEC} : main.o
	${OBJ}

clean :
	${RM} ${OBJ} ${EXEC}
