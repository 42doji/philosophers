#include "../inc/philosophers.h"

void	print_eat_count(t_philo *philo);
void	print_msg(t_philo *philo, int state);

void	print_eat_count(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print_mutex);
	printf("%d philo ate %d times\n", philo->id, philo->meal_count);
	pthread_mutex_unlock(philo->data->print_mutex);
}

void print_msg(t_philo *philo, int state)
{
	if (is_someone_dead(philo->data) || philo->is_dead == 1)
		return ;
	pthread_mutex_lock(philo->data->print_mutex);
	if (state == EATING)
		printf("%ld %d is eating\n", get_time() - get_start_time(philo), philo->id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", get_time() - get_start_time(philo), philo->id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", get_time() - get_start_time(philo), philo->id);
	else if (state == DEAD)
		printf("%ld %d died\n", get_time() - get_start_time(philo), philo->id);
	else if (state == FORK_TAKEN)
		printf("%ld %d has taken a fork\n", get_time() - get_start_time(philo), philo->id);
	pthread_mutex_unlock(philo->data->print_mutex);
}
