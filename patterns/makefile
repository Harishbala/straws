CXX = g++
CFLAGS = -c --std=c++17
INC = -I/usr/local/Cellar/boost/1.73.0/include/
all: adapter_pattern builder_pattern

adapter_pattern: adapter_pattern.o
	$(CXX) $< -o $@

adapter_pattern.o: adapter_pattern.cpp
	$(CXX) $(CFLAGS) $(INC) $<

builder_pattern : builder_pattern.o
	$(CXX) $< -o $@

builder_pattern.o : builder_pattern.cpp
	$(CXX) $(CFLAGS) $(INC) $<

clean:
	rm adapter_pattern
	rm builder_pattern
	rm *.o
