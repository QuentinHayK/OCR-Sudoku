# Compilers vars
CC=gcc
CPPFLAGS=
CFLAGS= `pkg-config --libs --cflags sdl2` -I/usr/local/include/freetype -lSDL2_image

LDFLAGS=
LDLIBS= -lm

SRC= src/main.c
jOBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

all:
	$ gcc src/main.c src/layer.c src/nn.c src/functions.c src/user_inputs_functions.c -o src/main `pkg-config --libs --cflags sdl2` -I/usr/local/include/freetype -lm -lSDL2_image -g

compile : $(EXEC)

$(EXEC) : $(OBJ)

-include ${DEP}

clean:
	$(RM) ${OBJ} ${DEP} ${PRG}

run:
	src/main

run-train-debug:
	gdb --args src/main --train "$(nn)" "$(folder)" "$(save)"

run-train:
	src/main --train "$(nn)" "$(folder)" "$(save)"

run-test:
	src/main --test "$(nn)" "$(save)"

# END Makefile

