#include "../inc/philosophers.h"

void	better_sleep(long time);

void better_sleep(long milliseconds)
{
	struct timeval	tv;
	long			start_time;
	long			time;

	gettimeofday(&tv, NULL);
	start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time = start_time;
	while (time < start_time + milliseconds)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
}