src = src/
srcDir = $(src)
includeDir = include/
lib = lib/
libDir = $(lib)

libs = $(wildcard $(libDir)*.dll.a)
libsFlag = $(libs:lib/lib%.dll.a=-l%)

program = program/
programDir = $(srcDir)$(program)
programSrc = $(wildcard $(programDir)*.c)
programObj = $(programSrc:%.c=%.o)

shared = shared/
sharedDir = $(srcDir)$(shared)
sharedSrc = $(wildcard $(sharedDir)*.c)
sharedObj = $(sharedSrc:%.c=%.o)

tests = tests/
testsDir = $(srcDir)$(tests)
testsBin = $(objDir)$(tests)
testsSrc = $(wildcard $(testsDir)*.c)
testsObj = $(testsSrc:%.c=%.o)

CC = gcc
CFLAGS = -I./$(includeDir) -I./$(sharedDir) -L./$(libDir) $(libsFlag) --ansi -g

build-run: build run

build: test program

rebuild: clean build

clean:
	rm -rf src/*/*.o
	rm -rf src/*/*.tmp
	rm -rf *.exe

shared: $(sharedObj)
	@echo
	@echo =====[Compiling shared]=====

test: tests
	@echo
	@echo =====[Running tests]=====
	./tests.exe

tests: shared $(testsObj)
	@echo
	@echo =====[Linking tests]=====
	$(CC) $(sharedObj) $(testsObj) -o ./tests.exe $(CFLAGS)

run: program
	@echo
	@echo =====[Running program]=====
	./program.exe

program: shared $(programObj)
	@echo
	@echo =====[Linking program]=====
	$(CC) $(sharedObj) $(programObj) -o ./program.exe $(CFLAGS)