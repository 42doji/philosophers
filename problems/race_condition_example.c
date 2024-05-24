#include <pthread.h>
#include <stdio.h>

int counter = 0; // 공유 자원

void *increment(void *arg)
{
	for (int i = 0; i < 1000000; i++) {
		counter++; // 임계 구역
	}
	return NULL;
}

int main()
{
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread2, NULL, increment, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Final counter value: %d\n", counter); // 예측 불가능한 결과
	return 0;
}