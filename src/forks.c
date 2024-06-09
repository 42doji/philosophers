#include "../inc/philosophers.h"

int init_forks(t_data *data)
{
	int i;

	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nb_phil);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->nb_phil)
	{
		data->forks[i].id = i;
		data->forks[i].is_taken = 0;
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
	if (!philo || !philo->first_fork || !philo->second_fork)
		return (NULL);
	if (philo->first_fork->id < philo->second_fork->id)
		return (philo->first_fork);
	return (philo->second_fork);
}

t_fork	*get_second_fork(t_philo *philo)
{
	if (!philo || !philo->first_fork || !philo->second_fork)
		return (NULL);
	if (philo->first_fork->id < philo->second_fork->id)
		return (philo->second_fork);
	return (philo->first_fork);
}

int take_forks(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);
	if (first_fork->is_taken || second_fork->is_taken)
		return (0);
	if (pthread_mutex_lock(&first_fork->mutex))
		return (0);
	first_fork->is_taken = 1;
	if (pthread_mutex_lock(&second_fork->mutex))
	{
		pthread_mutex_unlock(&first_fork->mutex);
		first_fork->is_taken = 0;
		return (0);
	}
	second_fork->is_taken = 1;
	print_msg(philo, FORK_TAKEN);
	return (1);
}

int drop_forks(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);
	first_fork->is_taken = 0;
	second_fork->is_taken = 0;
	pthread_mutex_unlock(&second_fork->mutex);
	pthread_mutex_unlock(&first_fork->mutex);
	print_msg(philo, FORK_DROPPED);
	return (0);
}