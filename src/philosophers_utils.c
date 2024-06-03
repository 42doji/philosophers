#include "../inc/philosophers.h"

int free_mutexes(t_data *data, int i)
{
	while (i >= 0)
	{
		/* may be need to unlock mutex before destroy */
		pthread_mutex_unlock(&data->philosophers[i].meal_mutex);
		pthread_mutex_destroy(&data->philosophers[i].meal_mutex);
		i--;
	}
	return (0);
}

int init_philos(t_data *data)
{
	int i;

	data->philosophers = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philosophers)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meal_count = 0;
		data->philosophers[i].first_fork = &data->forks[i];
		data->philosophers[i].second_fork = &data->forks[(i + 1) % data->philo_count];
		data->philosophers[i].state = INACTIVE;
		data->philosophers[i].data = data;
		if (pthread_mutex_init(&data->philosophers[i].meal_mutex, NULL))
			return (free_mutexes(data, i - 1));
		printf("philo: %d init_philos\n", i);
		i++;
	}
	return (1);
}

void	clean_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philosophers[i].id = -1;
		data->philosophers[i].meal_count = -1;
		data->philosophers[i].first_fork = NULL;
		data->philosophers[i].second_fork = NULL;
		data->philosophers[i].state = INACTIVE;
		pthread_mutex_destroy(&data->philosophers[i].meal_mutex);
		printf("philo: %d clean_philos\n", i);
		i++;
	}
	free(data->philosophers);
}

int init_datas(t_data *data)
{
	if (!init_forks(data))
		return (0);
	if (!init_philos(data))
	{
		free_forks(data, data->philo_count - 1);
		return (0);
	}
	return (1);
}