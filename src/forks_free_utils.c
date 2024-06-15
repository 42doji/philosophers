#include "../inc/philosophers.h"

void	clean_forks(t_data *data);
void	free_forks(t_data *data, int i);

void	clean_forks(t_data *data)
{
	int i;

	if (!data)
		return ;
	i = 0;
	while (i < data->nb_phil)
	{
		data->forks[i].id = -1;
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	free_forks(t_data *data, int i)
{
	if (!data || i < 0)
		return ;
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		data->forks[i].id = -1;
		i--;
	}
}
