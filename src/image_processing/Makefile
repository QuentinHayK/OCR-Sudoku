CC = gcc
CFLAGS = -Wall -Wextra `pkg-config --cflags sdl2 SDL2_image` -g
CPPFLAGS =

LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm

SRC = main.c grayscale.c matrix.c gaussian_blur.c gradients.c adaptative_threshold.c
OBJ = ${SRC:.c=.o}
EXEC = main

all : ${EXEC}

${EXEC} : ${OBJ}

clean :
	${RM} ${OBJ}
	${RM} ${EXEC}
	${RM} res/*.bmp
	clear
