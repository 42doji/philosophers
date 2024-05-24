# philosophers


```C
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

```C
#include <pthread.h>  
/* 
        * pthread_create, pthread_join, pthread_attr_t,
        * pthread_t, pthread_attr_init, pthread_attr_setdetachstate,
        * pthread_attr_destroy
*/
#include <stdio.h>    
// printf

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
}
```


#### Argument
- Local 변수를 넣어서는 안된다.
- static이나 malloc에 할당한 heap 메모리 주소를 전달한다.
- thread가 종료되면 메모리가 해제되기 때문에, 전달한 주소에 접근할 수 없다.
- 전달한 주소에 접근하려면 pthread_join을 사용한다.
- pthread_join을 사용하지 않으면 메모리 누수가 발생한다.


### Race condition
두개 이상의 프로세스가 공유된 자원에 동시에 접근할 때 발생하는 문제
mutex를 사용하여 해결한다.

- pthread_join
  - thread가 종료될 때까지 대기한다.
  - thread가 종료되면 메모리가 해제된다.
  

### Thread Termination
- Return
- pthread_exit(0)
- Thread Cancelation
    - kill
- pthread_cancel(pthread_self())
- pthread_exit(NULL)
- exit(0)
- abort()
- kill(getpid(), SIGKILL)
- pthread_exit(NULL)


### Main Thread가 죽으면 모든 thread가 죽는다.
- 하부 스레드가 죽어도 다른 스레드에는 영향이 없다.


### Main Thread Termination
- return (0)
- pthread_exit(0)
- exit(0)
- abort()
- kill(getpid(), SIGKILL)
- pthread_cancel(pthread_self())
- pthread_exit(NULL)


### Mutex
- pthread_mutex_init
- pthread_mutex_lock
- pthread_mutex_unlock
- pthread_mutex_destroy
- pthread_mutex_timedlock