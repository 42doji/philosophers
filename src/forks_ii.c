#include "../inc/philosophers.h"

int drop_forks(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);
	first_fork->is_taken = 0;
	second_fork->is_taken = 0;
	print_msg(philo, FORK_DROPPED);
	pthread_mutex_unlock(&second_fork->mutex);
	pthread_mutex_unlock(&first_fork->mutex);
	return (0);
}