CXX = g++
CFLAGS = -c --std=c++17
INC = -I/usr/local/Cellar/boost/1.73.0/include/
all: misc

misc: misc.o
	$(CXX) $(INC) $< -o $@

misc.o: misc.cpp
	$(CXX) $(CFLAGS) $(INC) $<
