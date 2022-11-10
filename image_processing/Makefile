CC = gcc
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
CPPFLAGS =

LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image`

SRC = main.c canny_edge_detector.c
OBJ = ${SRC:.c=.o}
EXEC = main

all : ${EXEC}

debug : ${EXEC}

${EXEC} : ${OBJ}

clean :
	${RM} ${OBJ}
	${RM} ${EXEC}
	${RM} *.png

