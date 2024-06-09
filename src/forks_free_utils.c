#include "../inc/philosophers.h"

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

void	free_forks(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		data->forks[i].id = -1;
		data->forks[i].is_taken = 0;
		i--;
	}
	free(data->forks);
}
