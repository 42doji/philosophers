#include "../inc/philosophers.h"

void	init_data_mutexes(t_data *data);
void	free_data_mutexes(t_data *data);
void	init_philo_mutexes(t_philo *philo);
void	free_philo_mutexes(t_philo *philo);

void	init_data_mutexes(t_data *data)
{
	data->nb_phil_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->nb_phil_mutex, NULL);
	data->time_to_die_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->time_to_die_mutex, NULL);
	data->time_to_eat_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->time_to_eat_mutex, NULL);
	data->time_to_sleep_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->time_to_sleep_mutex, NULL);
	data->meal_count_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->meal_count_mutex, NULL);
	data->all_ate_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->all_ate_mutex, NULL);
	data->dead_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->dead_mutex, NULL);
	data->everyone_ate_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->everyone_ate_mtx, NULL);
	data->print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->print_mutex, NULL);
}

void free_data_mutexes(t_data *data)
{
	pthread_mutex_destroy(data->nb_phil_mutex);
	free(data->nb_phil_mutex);
	pthread_mutex_destroy(data->time_to_die_mutex);
	free(data->time_to_die_mutex);
	pthread_mutex_destroy(data->time_to_eat_mutex);
	free(data->time_to_eat_mutex);
	pthread_mutex_destroy(data->time_to_sleep_mutex);
	free(data->time_to_sleep_mutex);
	pthread_mutex_destroy(data->meal_count_mutex);
	free(data->meal_count_mutex);
	pthread_mutex_destroy(data->all_ate_mutex);
	free(data->all_ate_mutex);
	pthread_mutex_destroy(data->dead_mutex);
	free(data->dead_mutex);
	pthread_mutex_destroy(data->everyone_ate_mtx);
	free(data->everyone_ate_mtx);
	pthread_mutex_destroy(data->print_mutex);
	free(data->print_mutex);
}
