#include "../inc/philosophers.h"

int	drop_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);
	if (first_fork->id < second_fork->id)
	{
		pthread_mutex_unlock(&first_fork->mutex);
		first_fork->is_taken = 0;
		pthread_mutex_unlock(&second_fork->mutex);
		second_fork->is_taken = 0;
	}
	else
	{
		pthread_mutex_unlock(&second_fork->mutex);
		second_fork->is_taken = 0;
		pthread_mutex_unlock(&first_fork->mutex);
		first_fork->is_taken = 0;
	}
	printf("%ld %d has dropped forks\n", get_time() - philo->start_time, philo->id);
	return (0);
}