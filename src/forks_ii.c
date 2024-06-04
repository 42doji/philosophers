#include "../inc/philosophers.h"

int	drop_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);
	return (0);
}