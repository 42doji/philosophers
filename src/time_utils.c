#include "../inc/philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


void test_time(void) {
	long start_time;
	long now;

	start_time = get_time();
	usleep(1000);
	now = get_time();
	printf("start_time: %ld\n", start_time);
	printf("now: %ld\n", now);
	printf("diff: %ld\n", now - start_time);
}


void			test_eat(t_philo *philo)
{
	struct timeval	start_time;
	struct timeval	end_time;
	long			requested_eat_time;
	long			actual_eat_time;

	requested_eat_time = philo->data->time_to_eat * 1000;
	gettimeofday(&start_time, NULL);
	usleep(requested_eat_time);
	gettimeofday(&end_time, NULL);
	actual_eat_time = (end_time.tv_sec * 1000 + end_time.tv_usec / 1000) - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	printf("requested_eat_time: %ld\n", requested_eat_time / 1000);
	printf("actual_eat_time: %ld\n", actual_eat_time);
}