#include "../inc/philosophers.h"

void	better_sleep(long time);

void better_sleep(long sleep_time)
{
	long start_time;

	start_time = get_time();
	while ((get_time() - start_time) < sleep_time)
	{
		printf("get_time() - start_time: %ld\n", get_time() - start_time);
		usleep(	(sleep_time - (get_time() - start_time)) * 0.5);
	}
}