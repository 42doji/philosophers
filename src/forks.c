#include "../inc/philosophers.h"

void	free_forks(t_data *data, int i)
{
	while (i >= 0)
	{
		if (&data->forks[i].mutex)
			pthread_mutex_destroy(&data->forks[i].mutex);
		i--;
	}
}

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
			free(data->forks);
			break;
		}
		i++;
	}
	return (1);
}

void	clean_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_phil)
	{
		data->forks[i].id = -1;
		data->forks[i].is_taken = 0;
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
}

t_fork	*get_first_fork(t_philo *philo)
{
	if (philo->first_fork->id < philo->second_fork->id)
		return (philo->first_fork);
	return (philo->second_fork);
}

t_fork	*get_second_fork(t_philo *philo)
{
	if (philo->first_fork->id < philo->second_fork->id)
		return (philo->second_fork);
	return (philo->first_fork);
}

int	take_forks(t_philo *philo)
{
	t_fork *first_fork;
	t_fork *second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);

	// 포크를 잡기 위한 동기화 강화
	pthread_mutex_lock(&first_fork->mutex);
	if (first_fork->is_taken)
	{
		pthread_mutex_unlock(&first_fork->mutex);
		return (0);
	}

	pthread_mutex_lock(&second_fork->mutex);
	if (second_fork->is_taken)
	{
		pthread_mutex_unlock(&second_fork->mutex);
		pthread_mutex_unlock(&first_fork->mutex);
		return (0);
	}

	first_fork->is_taken = 1;
	second_fork->is_taken = 1;
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);

	philo->first_fork = first_fork;
	philo->second_fork = second_fork;

	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d has taken both forks\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->print_mutex);

	return (1);
}