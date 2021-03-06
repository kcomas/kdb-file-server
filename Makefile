
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
test: test1 test2

.PHONY: test1
test1: CCFLAGS=$(TESTFLAGS)
test1: $(OBJECTS) ./test/test1.o
	$(CC) $(TESTFLAGS) $^ $(CSHAREDO) -o ./test/test1

.PHONY: test2
test2: CCFLAGS=$(TESTFLAGS)
test2: $(OBJECTS) ./test/test2.o
	$(CC) $(TESTFLAGS) $^ $(CSHAREDO) -o ./test/test2

.PHONY: clean
clean:
	rm -fv test/test1
	rm -fv test/test2
	rm -fv test/*.o
	rm -fv src/*.o
