CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -O3 `pkg-config --cflags sdl2 SDL2_image` -g
CPPFLAGS =

LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm

SRC = main.c grayscale.c matrix.c gaussian_blur.c gradients.c
OBJ = ${SRC:.c=.o}
EXEC = main

all : ${EXEC}

${EXEC} : ${OBJ}

clean :
	${RM} ${OBJ}
	${RM} ${EXEC}
	${RM} res/*.bmp
	clear
