CC=gcc
CXX=g++
CXXFLAGS=--std=c++11
OPT_FLAG= -o

all: tree linked_list

tree: tree.o
	$(CXX) $< $(OPT_FLAG) $@

linked_list: linked_list.o
	$(CC) $< $(OPT_FLAG) $@

clean:
	rm *.o
	rm tree
	rm linked_list

