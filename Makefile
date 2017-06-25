
CC=gcc
SRC=./src
KDB=./kdb
TARGET=64
CO=c.o
KDBFLAGS=-DKXVER=3 -m$(TARGET)
CCFLAGS=-shared -fPIC $(KDBFLAGS)
TESTFLAGS=-g -Wall $(KDBFLAGS) -lpthread
CSHAREDO=$(KDB)/l$(TARGET)/$(CO)

SOURCES:=$(shell find $(SRC) -name '*.c')
OBJECTS=$(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: test
test: $(OBJECTS) ./test/test.o
	$(CC) $(TESTFLAGS) $^ $(CSHAREDO) -o ./test/test

.PHONY: clean
clean:
	rm -fv test/test
	rm -fv test/test2
	rm -fv test/*.o
	rm -fv src/*.o
