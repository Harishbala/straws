CC=gcc
CXX=g++
CXXFLAGS=--std=c++17
OPT_FLAG= -o

COMPONENTS = tree linked_list strings
all: $(COMPONENTS) 

tree: tree.o
	$(CXX) $< $(OPT_FLAG) $@

linked_list: linked_list.o
	$(CC) $< $(OPT_FLAG) $@

strings: strings.o
	$(CXX) $< $(OPT_FLAG) $@

clean:
	rm *.o
	rm $(COMPONENTS)

