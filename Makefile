
CC=gcc
SRC=./src
CCFLAGS=-I $(SRC) -shard -fPIC -DKXVER=3

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

.PHONY: test
test: CCFLAGS=-g -Wall
test: $(SRC)/file_server.o $(SRC)/test.o
	$(CC) $(CCFLAGS) $^ -o test 

.PHONY: clean
clean:
	rm -fv test
	rm -fv src/*.o
