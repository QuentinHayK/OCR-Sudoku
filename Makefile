# Compilers vars
CC=gcc
CPPFLAGS=
CFLAGS= `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall
LDFLAGS=
LDLIBS= -lm

SRC= src/main.c
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

all: ${PRG}

-include ${DEP}

clean:
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}
	
run:
	src/main
	
run-learn:
	src/main --learn
	
run-test:
	src/main --test

# END Makefile

