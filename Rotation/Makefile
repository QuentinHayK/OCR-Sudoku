# Makefile
 
CC = gcc
CPPFLAGS =
CCFLAGS =  -Wall -Wextra -O3  `pkg-config --cflags sdl2 SDL2_image`                                                                                                                      
LDFLAGS = 
LDLIBS =  `pkg-config --libs sdl2 SDL2_image` -lm -ldl
 
all: rotation

SRC = rotation.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}
 
rotation: rotation.o
 
.PHONY: clean
 
clean:
	${RM} ${OBJ}
	${RM} ${EXE}

run:
	$ ./rotation "images/Sudoku1.png" "$(angle)"

# END

