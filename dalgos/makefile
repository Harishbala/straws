CC=gcc
CXX=g++
CXXFLAGS=--std=c++17
LDFLAGS=-L /usr/local/lib/
OPT_FLAG= -o

COMPONENTS = linked_list dalgos_test 
all: $(COMPONENTS) 

dalgos_test: dalgos_test.o tree.hpp graph.hpp
	$(CXX) $< $(OPT_FLAG) $@ $(LDFLAGS) -l gtest

dalgos_test.o: dalgos_test.cpp tree.hpp strings.hpp arrays.hpp
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm *.o
	rm $(COMPONENTS)

