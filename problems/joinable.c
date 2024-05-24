#include "../philosophers.h"

void	print_message(void *ptr)
{
	char *message;

	message = (char *)ptr;
	printf("%s", message);
}

int main(int argc, char *argv[])
{
	// argv[0] = ./a.out
	// argv[1] = 철학자가 식사하지 않았거나 식사를 시작한 후 죽는데 걸리는 시간
	// argv[2] = 철학자가 식사를 먹는데 걸리는 시간
	// argv[3] = 철학자가 잠자는데 걸리는 시간
	// argv[4] = 철학자가 식사하는 횟수
	if (argc != 4 || argc != 5)
		return (1);

	pthread_t 		thread;
	pthread_attr_t 	attr;
	pthread_mutex_t *fork;
	char 			*message = "hello world.\n";

	fork = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(fork, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&thread, &attr, (void *)print_message, (void *)message);
	printf("main: end.\n");
	pthread_join(thread, NULL);
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(fork);
	free(fork);
	return (0);
}