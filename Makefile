
CC=gcc
SRC=./src
CCFLAGS=-I $(SRC) -shard -fPIC -DKXVER=3

SOURCES:=$(shell find $(SRC) -name '*.c')
OBJECTS=$(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

PHONY: test
test: CCFLAGS=-g -Wall
test: $(OBJECTS) ./test/test.o
	$(CC) $(CCFLAGS) $^ -o ./test/test

.PHONY: clean
clean:
	rm -fv test/test
	rm -fv src/*.o
