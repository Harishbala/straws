CXX = g++
CFLAGS = -c --std=c++17
INC = -I/usr/local/Cellar/boost/1.73.0/include/
all: adapter_pattern

adapter_pattern: adapter_pattern.o
	$(CXX) $(INC) $< -o $@

adapter_pattern.o: adapter_pattern.cpp
	$(CXX) $(CFLAGS) $(INC) $<

clean:
	rm *.o
	rm adapter_pattern
