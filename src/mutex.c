#include "../inc/philosophers.h"

void	init_data_mutexes(t_data *data)
{
	data->nb_phil_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->time_to_die_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->time_to_eat_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->time_to_sleep_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->meal_count_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->all_ate_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->dead_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->everyone_ate_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
}

void	free_data_mutexes(t_data *data)
{
	free(data->nb_phil_mutex);
	free(data->print_mutex);
	free(data->time_to_die_mutex);
	free(data->time_to_eat_mutex);
	free(data->time_to_sleep_mutex);
	free(data->meal_count_mutex);
	free(data->all_ate_mutex);
	free(data->dead_mutex);
	free(data->everyone_ate_mtx);
}