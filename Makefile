
CC=gcc
SRC=./src
KDB=./kdb
TARGET=64
CO=c.o
CCFLAGS=-shared -fPIC -DKXVER=3 -m$(TARGET)
CSHAREDO=$(KDB)/l$(TARGET)/$(CO)

SOURCES:=$(shell find $(SRC) -name '*.c')
OBJECTS=$(SOURCES:.c=.o)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

PHONY: test
test: CCFLAGS=-I $(KDB) -g -Wall -m$(TARGET) -lpthread
test: $(OBJECTS) ./test/test.o
	$(CC) $(CCFLAGS) $^ $(CSHAREDO) -o ./test/test

.PHONY: clean
clean:
	rm -fv test/test
	rm -fv test/*.o
	rm -fv src/*.o
