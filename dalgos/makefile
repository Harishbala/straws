CC=g++
CFLAGS= --std=c++11
OPT_FLAG= -o

all: tree

tree: tree.o
	$(CC) $< $(CFLAGS) $(OPT_FLAG) $@

clean:
	rm *.o
	rm tree
