#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t lock;
int counter;
pthread_attr_t attr;

void *increment(void *arg)
{
	int 	i;
	void	*res;

	printf("thread id: %d\n", *(int *)arg);
	free(arg);
	i = 0;
	pthread_mutex_lock(&lock);
	while (i < 1000000) {
		counter++;
		i++;
	}
	pthread_mutex_unlock(&lock);
	res = malloc(sizeof(int));
	if (!res)
	{
		perror("malloc res error");
		return (NULL);
	}
	*(int *)res = counter;
	return ((void *)res);
}

void	create_threads(pthread_t *thread_handle, int thread_id)
{
	int *_thread_id;
	_thread_id = malloc(sizeof(int));
	*_thread_id =thread_id;
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(thread_handle, &attr, increment, (void *)_thread_id);
}


int main(int argc, char *argv[])
{
	void *res1, *res2;
	pthread_t thread1, thread2;

	counter = 0;
	pthread_mutex_init(&lock, NULL);
	create_threads(&thread1, 1);
	create_threads(&thread2, 2);
	pthread_join(thread1, &res1);
	pthread_join(thread2, &res2);

	if (res1)
	{
		printf("res1: %d\n",*(int *)res1);
	}
	if (res2)
	{
		printf("res2: %d\n",*(int *)res2);
	}
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&lock);
	free(res1);
	free(res2);
	return (0);
}