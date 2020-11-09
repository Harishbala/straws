all: tasks.cpp process_api.c
	g++ --std=c++17 tasks.cpp -lpthread -o tasks
	gcc process_api.c -o papi
	g++ --std=c++17 threads.cpp -lpthread -o threads
