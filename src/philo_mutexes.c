#include "../inc/philosophers.h"

void	allocate_philo_mutexes(t_philo *philo)
{
	philo->meal_count_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->meal_count_mutex, NULL);
	philo->is_full_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->is_full_mutex, NULL);
	philo->thought_count_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->thought_count_mutex, NULL);
	philo->start_time_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->start_time_mutex, NULL);
	philo->last_meal_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->last_meal_mutex, NULL);
	philo->state_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->state_mutex, NULL);
	philo->print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->print_mutex, NULL);
}


void set_philo_mutexes(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_phil)
	{
		allocate_philo_mutexes(&data->phils[i]);
		i++;
	}
}
void free_philo_mutexes(t_philo *philo)
{
	if (philo->meal_count_mutex)
	{
		pthread_mutex_destroy(philo->meal_count_mutex);
		free(philo->meal_count_mutex);
		philo->meal_count_mutex = NULL;
	}
	if (philo->is_full_mutex)
	{
		pthread_mutex_destroy(philo->is_full_mutex);
		free(philo->is_full_mutex);
		philo->is_full_mutex = NULL;
	}
	if (philo->thought_count_mutex)
	{
		pthread_mutex_destroy(philo->thought_count_mutex);
		free(philo->thought_count_mutex);
		philo->thought_count_mutex = NULL;
	}
	if (philo->start_time_mutex)
	{
		pthread_mutex_destroy(philo->start_time_mutex);
		free(philo->start_time_mutex);
		philo->start_time_mutex = NULL;
	}
	if (philo->last_meal_mutex)
	{
		pthread_mutex_destroy(philo->last_meal_mutex);
		free(philo->last_meal_mutex);
		philo->last_meal_mutex = NULL;
	}
	if (philo->state_mutex)
	{
		pthread_mutex_destroy(philo->state_mutex);
		free(philo->state_mutex);
		philo->state_mutex = NULL;
	}
	if (philo->print_mutex)
	{
		pthread_mutex_destroy(philo->print_mutex);
		free(philo->print_mutex);
		philo->print_mutex = NULL;
	}
}
