CC = gcc
CFLAGS = -std=c2x \
  -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings \
  -O2
objects = array.o meteoyearlybin_misc.o
executable = meteoyearlybin_misc

.PHONY: all clean dist

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

dist: clean
	zip "$(CURDIR).zip" *.c *.h makefile

$(executable): $(objects)
	$(CC) $(objects) -o $(executable)

array.o: array.c array.h
meteoyearlybin_misc.o: meteoyearlybin_misc.c array.h
