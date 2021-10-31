srcFiles = $(wildcard *.c)
objFiles = $(srcFiles:%.c=bin/obj/%.o)
output = bin/rel/program
CC = gcc
CFLAGS = -I. --ansi

all: clean build run

clean:
	rm -rf bin/
	mkdir bin/
	mkdir bin/obj
	mkdir bin/rel
	@echo "Removing files from bin/"

build: $(objFiles)
	@echo "Linking $(output)"
	$(CC) $(objFiles) -o $(output)

run:
	@echo "Running $(output)"
	bin/rel/program

bin/obj/%.o : %.c
	@echo "Compiling $<"
	$(CC) -c $(CFLAGS) $< -o $@