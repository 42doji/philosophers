#include "../inc/philosophers.h"

void	clean_philos(t_data *data);
void	free_forks(t_data *data, int i);
void	clean_datas(t_data *data);
int 	init_philos(t_data *data);


void	clean_philos(t_data *data)
{
	free(data->phils);
	data->phils = NULL;
}

void	clean_datas(t_data *data)
{
	clean_forks(data);
	free_data_mutexes(data);
	clean_philos(data);
	free(data->phils);
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
		data->phils[i].thought_count = 0;
		data->phils[i].start_time = 0;
		i++;
	}
	return (1);
}

void	init_data_attr(t_data *data)
{
	data->fulled_philo_count = 0;
	data->someone_is_dead = 0;
}

int init_datas(t_data *data)
{
	if (!data)
		return (0);
	if (!init_forks(data))
		return (error_handler(data, MALLOC_ERROR));
	if (!init_philos(data))
	{
		free_forks(data, data->nb_phil - 1);
		free(data->forks);
		return (error_handler(data, MALLOC_ERROR));
	}
	init_data_mutexes(data);
	init_data_attr(data);
	return (1);
}
