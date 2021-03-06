// Exercises from operating system in three easy step book. - http://pages.cs.wisc.edu/~remzi/OSTEP/
#include <iostream>

#if __linux__
#include <cassert>
#endif

#include <pthread.h>

static volatile int counter = 0;

pthread_mutex_t lock;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

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
	pthread_cond_signal(&condition);
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

	int loop_ctrl = 1e7;
	std::cout << "Loop control: " << loop_ctrl << '\n';

	int wait_count = 0;
	while (wait_count < 2) {
		pthread_mutex_lock(&lock);
		pthread_cond_wait(&condition, &lock);
		pthread_mutex_unlock(&lock);
		++wait_count;
	}

	pthread_mutex_destroy(&lock);
	std::cout<<"counter ="<<counter<<"\n";
	return 0;
}
