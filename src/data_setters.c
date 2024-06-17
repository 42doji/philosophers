#include "../inc/philosophers.h"

void add_full_philo(t_data *data);
int is_all_ate(t_data *data);

void add_full_philo(t_data *data)
{
	pthread_mutex_lock(data->fulled_philo_count_mutex);
	data->fulled_philo_count++;
	pthread_mutex_unlock(data->fulled_philo_count_mutex);
}


int	is_everyone_ate(t_data *data)
{
	int	res;
	
	pthread_mutex_lock(data->everyone_ate_mutex);
	res = data->everyone_ate;
	pthread_mutex_unlock(data->everyone_ate_mutex);
	return (res);
}

int is_all_ate(t_data *data)
{
	int	ate_phils;
	int nb_phils;

	pthread_mutex_lock(data->everyone_ate_mutex);
	ate_phils = data->fulled_philo_count;
	pthread_mutex_unlock(data->everyone_ate_mutex);
	pthread_mutex_lock(data->nb_phil_mutex);
	nb_phils = data->nb_phil;
	pthread_mutex_unlock(data->nb_phil_mutex);
	if (ate_phils == nb_phils)
	{
		pthread_mutex_lock(data->everyone_ate_mutex);
		data->everyone_ate = 1;
		pthread_mutex_unlock(data->everyone_ate_mutex);
		return (1);
	}
	return (0);
}