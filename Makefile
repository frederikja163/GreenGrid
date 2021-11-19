src = src/
srcDir = $(src)
include := include/
includeDir := $(include)
lib = lib/
libDir := $(lib)

libs := $(wildcard $(libDir)*.dll.a)
libsFlag := $(libs:lib/lib%.dll.a=-l%)

program = program/
programDir := $(srcDir)$(program)
programSrc := $(wildcard $(programDir)*.c)
programObj := $(programSrc:%.c=%.o)

shared = shared/
sharedDir := $(srcDir)$(shared)
sharedSrc := $(wildcard $(sharedDir)*.c)
sharedObj := $(sharedSrc:%.c=%.o)

tests = tests/
testsDir := $(srcDir)$(tests)
testsBin := $(objDir)$(tests)
testsSrc := $(wildcard $(testsDir)*.c)
testsObj := $(testsSrc:%.c=%.o)

CC = gcc
CFLAGS = -I./$(includeDir) -I./$(sharedDir) -L./$(libDir) $(libsFlag) --ansi

build-run: build run

build: test build-program

rebuild: clean build

clean:
	rm -rf src/*/*.o
	rm -rf *.exe

build-shared: $(sharedObj)
	@echo "Compiling shared"

test: build-tests
	@echo ===[Running tests]===
	./tests.exe

build-tests: build-shared $(testsObj)
	@echo "Building tests"
	$(CC) $(sharedObj) $(testsObj) -o ./tests.exe

run: build-program
	@echo ===[Running program]===
	./program.exe

build-program: build-shared $(programObj)
	@echo "Building program"
	$(CC) $(sharedObj) $(programObj) -o ./program.exe