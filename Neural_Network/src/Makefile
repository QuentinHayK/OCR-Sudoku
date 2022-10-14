CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O2 `pkg-config --libs --cflags sdl2` -I/usr/local/include/freetype -lSDL2_image
CPPFLAGS =

LDFLAGS =
LDLIBS = -lm -lSDL2_image -g

SRC = main.c usefull/matrix.c usefull/functions.c nn.c
OBJ = ${SRC:.c=.o}
EXEC = main

all : ${EXEC}
	@echo ${EXEC}

${EXEC} : ${OBJ}

clean :
	${RM} ${OBJ} ${EXEC}
