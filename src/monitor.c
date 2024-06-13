#include "../inc/philosophers.h"

int is_someone_dead(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_phil)
	{
		if (data->phils[i].state == EATING)
		{
			if (get_time() - data->phils[i].last_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->mutex);
				printf("%ld %d died\n", get_time() - data->phils[i].start_time, data->phils[i].id);
				set_philo_state(&data->phils[i], DEAD);
				pthread_mutex_unlock(&data->mutex);
				return (1);
			}
		}
		i++;
	}
	return (0);
}


void	*monitoring(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	start_simulation(data);
	while (1)
	{
		if (is_someone_dead(data))
			break ;
		if (data->everyone_is_full && data->meal_count != -1)
			break ;
		usleep(100);
	}
	return (NULL);
}


void	create_monitor_thread(void	*arg)
{
	t_data *data;

	data = (t_data *)arg;
	pthread_create(&data->monitor_thread, NULL, monitoring, arg);
	pthread_detach(data->monitor_thread);
}