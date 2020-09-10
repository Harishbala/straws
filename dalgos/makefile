CC=gcc
CXX=g++
CXXFLAGS=--std=c++17
LDFLAGS=-L /usr/local/lib/
OPT_FLAG= -o

COMPONENTS = linked_list strings dalgos_test 
all: $(COMPONENTS) 

dalgos_test: dalgos_test.o tree.hpp
	$(CXX) $< $(OPT_FLAG) $@ $(LDFLAGS) -l gtest

dalgos_test.o: dalgos_test.cpp tree.hpp
	$(CXX) -c $(CXXFLAGS) $<

clean:
	rm *.o
	rm $(COMPONENTS)

