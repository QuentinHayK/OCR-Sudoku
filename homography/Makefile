# Makefile
 
CC = gcc
CPPFLAGS =
CCFLAGS = -g  -Wall -Wextra -O3  `pkg-config --cflags sdl2 SDL2_image` -fsanitize=address                                                                                                                     
LDFLAGS = -fsanitize=address
LDLIBS =  `pkg-config --libs sdl2 SDL2_image` -lm -ldl
 
all: homographic

SRC = homographic.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}
 
rotation: homographic.o
 
.PHONY: clean
 
clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END

