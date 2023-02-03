# library name
LIBRARY_NAME = liblm.a

# source files
SOURCES = $(wildcard src/*.c)

# object files
OBJECTS = $(SOURCES:.c=.o)

# compiler flags
CFLAGS = -Wall -Wextra -Werror -pedantic -Iinclude

# build target
all: $(OBJECTS)
	ar rcs $(LIBRARY_NAME) $^

# object files from sources
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

# clean up object files and library
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(LIBRARY_NAME)
