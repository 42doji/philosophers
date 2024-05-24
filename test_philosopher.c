#include <pthread.h>
#include <stdio.h>

void	*print(void *arg)
{
	/*
	 * start rountine 함수 : 스레드가 실행할 함수
	 * 스레드 함수의 반환값은 void *로 반환해야 한다.
	 * 스레드 함수의 반환값은 pthread_join() 함수를 통해 받을 수 있다.
	 */
	char *s;

	s = (char *)arg;
	printf("%s\n", s);
	return ((void *)0);    // 반환값이 없으면 컴파일러가 경고를 띄움
}

int	main(int argc, char *argv[])
{
	pthread_t	thread;
	// pthread_t : 스레드 식별자
	pthread_attr_t	attr;
	// pthread_attr_t : 스레드 속성을 저장하는 구조체

	pthread_attr_init(&attr);
	// 스레드 속성 초기화, 하지 않을 시 Segmentation fault 발생.
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	/*
	 * setdetachstate : 스레드의 종료를 기다릴지 여부를 설정
	 * PTHREAD_CREATE_JOINABLE은 기다림,
	 * PTHREAD_CREATE_DETACHED는 기다리지 않음
	 */
	 pthread_create(&thread, &attr, print, (void *)"hello world");
	 /*
	  * pthread_create : 새로운 스레드를 생성
	  */
	pthread_join(thread, NULL);
	/*
	 * pthread_join : 스레드가 종료될 때까지 기다림
	 * 첫 번째 인자 : 종료될 스레드 식별자
	 * 두 번째 인자 : 스레드의 반환값을 저장할 변수
	 */
	pthread_attr_destroy(&attr);
	// 스레드 속성을 제거
	printf("main: end\n");

	return (0);

	// newthread : thread to create
	// attr : thread attributes which can be NULL for default values
	// start_routine : function to be executed by the new thread
	// arg : argument to be passed to the start_routine
}