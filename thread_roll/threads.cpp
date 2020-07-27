// Exercises from operating system in three easy step book. - http://pages.cs.wisc.edu/~remzi/OSTEP/
#include <iostream>
#include <pthread.h>

static volatile int counter = 0;

pthread_mutex_t lock;

void* thread_to_run(void *arg)
{
	pthread_mutex_lock(&lock);
	std::cout<<"Thread "<<*static_cast<int*>(arg)<<" started.\n";
	pthread_mutex_unlock(&lock);

	int i;
	for(i = 0; i < 1e7; i++)
	{
		pthread_mutex_lock(&lock);
		counter = counter + 1;
		pthread_mutex_unlock(&lock);
	}
	return nullptr;
}

int main()
{
	int rc = pthread_mutex_init(&lock, nullptr);
	assert(rc == 0);
	if(rc != 0) return -1;

	pthread_t p1, p2;

	int t1_arg = 1, t2_arg = 2;
	pthread_create(&p1, nullptr, thread_to_run, &t1_arg);
	pthread_create(&p2, nullptr, thread_to_run, &t2_arg);

	pthread_join(p1, nullptr);
	pthread_join(p2, nullptr);

	pthread_mutex_destroy(&lock);
	std::cout<<"counter ="<<counter<<"\n";
	return 0;
}