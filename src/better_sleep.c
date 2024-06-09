#include "../inc/philosophers.h"

void	better_sleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(10);
}
