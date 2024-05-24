#include <pthread.h>
#include <stdio.h>

int counter = 0;
pthread_mutex_t lock;

void *increment(void *arg)
{
	for (int i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&lock); // 임계 구역 시작
		counter++;
		pthread_mutex_unlock(&lock); // 임계 구역 끝
	}
	return NULL;
}

int main()
{
	pthread_t thread1, thread2;

	pthread_mutex_init(&lock, NULL); // 뮤텍스 초기화

	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread2, NULL, increment, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&lock); // 뮤텍스 파괴

	printf("Final counter value: %d\n", counter); // 예상 가능한 결과
	return 0;
}