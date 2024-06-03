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

