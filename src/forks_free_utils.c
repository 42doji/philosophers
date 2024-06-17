#include "../inc/philosophers.h"

void	clean_forks(t_data *data);
void	free_forks(t_data *data, int i);

void	clean_forks(t_data *data);
void	free_forks(t_data *data, int i);

void clean_forks(t_data *data)
{
	int	i;

	if (!data || !data->forks)
		return;
	i = 0;
	while (i < data->nb_phil)
	{
		if (pthread_mutex_destroy(&data->forks[i].mutex) != 0)
			fprintf(stderr, "Failed to destroy mutex %d\n", i);
		i++;
	}
	free(data->forks);
}

void	free_forks(t_data *data, int i)
{
	if (!data || i < 0)
		return ;
	while (i >= 0)
	{
		if (pthread_mutex_destroy(&data->forks[i].mutex) != 0)
			fprintf(stderr, "Failed to destroy mutex %d\n", i);
		data->forks[i].id = -1;
		i--;
	}
}
