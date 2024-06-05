#include "../inc/philosophers.h"

int drop_forks(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);

	pthread_mutex_lock(&first_fork->mutex);
	pthread_mutex_lock(&second_fork->mutex);

	first_fork->is_taken = 0;
	second_fork->is_taken = 0;

	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);

	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d has dropped forks\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);

	return (0);
}