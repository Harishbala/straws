#include <iostream>
#include <pthread.h>

void thread_to_run(void *arg)
{
	std::cout<<"Hello, I am a thread.\n";
}

int main()
{
	pthread_t p1, p2;

	pthread_create(&p1, nullptr, thread_to_run, nullptr);
	pthread_create(&p2, nullptr, thread_to_run, nullptr);
	pthread_join(p1, nullptr);
	pthread_join(p2, nullptr);
	return 0;
}