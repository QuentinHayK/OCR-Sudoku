# Compilers vars
CC=gcc
CPPFLAGS= -g
CFLAGS= `pkg-config --libs --cflags sdl2` -I/usr/local/include/freetype -lSDL2_image

LDFLAGS=
LDLIBS= -lm

SRCDIR= src/
SRC = $(shell find $(SRCDIR) -name '*.c')
OBJ= $(SRC:%.c=%.o)
DEP= $(SRC:%.c=%.d)
EXEC= main

all:
	$ gcc src/main.c src/layer.c src/nn.c src/functions.c src/user_inputs_functions.c -o src/main `pkg-config --libs --cflags sdl2` -I/usr/local/include/freetype -lm -lSDL2_image -g


allbis: $(EXEC)

$(EXEC): $(OBJ)

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

