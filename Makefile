# Compilers vars
CC=gcc
CPPFLAGS=
CFLAGS= `pkg-config --libs --cflags sdl2` -I/usr/local/include/freetype
LDFLAGS=
LDLIBS= -lm

SRC= src/main.c
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

all: 
	$ gcc src/main.c -o src/main `pkg-config --libs --cflags sdl2` -I/usr/local/include/freetype -lm

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

