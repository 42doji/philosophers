#include "../inc/philosophers.h"

int init_forks(t_data *data);
t_fork	*get_first_fork(t_philo *philo);
t_fork	*get_second_fork(t_philo *philo);
int take_forks(t_philo *philo);
int drop_forks(t_philo *philo);

int init_forks(t_data *data)
{
	int	i;

	if (!data)
		return (error_handler(data, ARG_ERROR));
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nb_phil);
	if (!data->forks)
		error_handler(data, MALLOC_ERROR);
	i = 0;
	while (i < data->nb_phil)
	{
		data->forks[i].id = i;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
		{
			free_forks(data, i - 1);
			break;
		}i++;
	}
	return (1);
}


t_fork	*get_first_fork(t_philo *philo)
{
	if (!philo)
		return (NULL);
	if (!philo->first_fork || !philo->second_fork)
		error_handler(philo->data, MUTEX_ERROR);
	if (philo->first_fork->id < philo->second_fork->id)
		return (philo->first_fork);
	return (philo->second_fork);
}

t_fork	*get_second_fork(t_philo *philo)
{
	if (!philo)
		return (NULL);
	if (!philo->first_fork || !philo->second_fork)
		error_handler(philo->data, MUTEX_ERROR);
	if (philo->first_fork->id < philo->second_fork->id)
		return (philo->second_fork);
	return (philo->first_fork);
}

int take_forks(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);
	pthread_mutex_lock(&first_fork->mutex);
	print_msg(philo, FORK_TAKEN);
	pthread_mutex_lock(&second_fork->mutex);
	print_msg(philo, FORK_TAKEN);
	return (1);
}

int drop_forks(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;

	if (!philo)
		return (0);
	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);
	pthread_mutex_unlock(&second_fork->mutex);
	print_msg(philo, FORK_DROPPED);
	pthread_mutex_unlock(&first_fork->mutex);
	print_msg(philo, FORK_DROPPED);
	return (1);
}