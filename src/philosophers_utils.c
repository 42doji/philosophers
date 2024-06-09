#include "../inc/philosophers.h"

void clean_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_phil)
	{
		data->phils[i].id = -1;
		data->phils[i].meal_count = -1;
		data->phils[i].first_fork = NULL;
		data->phils[i].second_fork = NULL;
		data->phils[i].state = INACTIVE;
		data->phils[i].last_meal = -1;
		data->phils[i].is_full = 0;
		pthread_mutex_destroy(&data->phils[i].meal_mutex);
		i++;
	}
	free(data->phils);
	data->phils = NULL;
}

void	clean_datas(t_data *data)
{
	clean_philos(data);
	clean_forks(data);
}

int init_philos(t_data *data)
{
	int i;

	data->phils = (t_philo *)malloc(sizeof(t_philo) * data->nb_phil);
	if (!data->phils)
		return (0);
	i = 0;
	while (i < data->nb_phil)
	{
		data->phils[i].id = i + 1;
		data->phils[i].meal_count = 0;
		data->phils[i].first_fork = &data->forks[i];
		data->phils[i].second_fork = &data->forks[(i + 1) % data->nb_phil];
		data->phils[i].state = INACTIVE;
		data->phils[i].data = data;
		data->phils[i].is_full = 0;
		if (pthread_mutex_init(&data->phils[i].meal_mutex, NULL))
		{
			free_mutexes(data, i - 1);
			free(data->phils);
			return (0);
		}
		i++;
	}
	return (1);
}

int init_datas(t_data *data)
{
	static pthread_mutex_t mutex;

	mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data->mutex = mutex;
	if (!init_forks(data))
		return (0);
	if (!init_philos(data))
	{
		free_forks(data, data->nb_phil - 1);
		free(data->forks);
		return (0);
	}
	return (1);
}
