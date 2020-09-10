CC=gcc
CXX=g++
CXXFLAGS=--std=c++17
INC=-I/usr/local/include/gtes
LDFLAGS=-L /usr/local/lib/
OPT_FLAG= -o

COMPONENTS = linked_list strings dalgos_test
all: $(COMPONENTS) 

linked_list: linked_list.o
	$(CC) $< $(OPT_FLAG) $@

strings: strings.o
	$(CXX) $< $(OPT_FLAG) $@

dalgos_test: dalgos_test.o 
	$(CXX) $< $(OPT_FLAG) $@ $(LDFLAGS) -l gtest

clean:
	rm *.o
	rm $(COMPONENTS)

