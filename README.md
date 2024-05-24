# philosophers


```C
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
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