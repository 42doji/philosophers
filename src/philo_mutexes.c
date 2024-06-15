#include "../inc/philosophers.h"

void init_philo_mutexes(t_philo *philo)
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

void free_philo_mutexes(t_philo *philo)
{
	if (philo->meal_count_mutex) {
		pthread_mutex_destroy(philo->meal_count_mutex);
		free(philo->meal_count_mutex);
	}

	if (philo->is_full_mutex) {
		pthread_mutex_destroy(philo->is_full_mutex);
		free(philo->is_full_mutex);
	}

	if (philo->thought_count_mutex) {
		pthread_mutex_destroy(philo->thought_count_mutex);
		free(philo->thought_count_mutex);
	}

	if (philo->start_time_mutex) {
		pthread_mutex_destroy(philo->start_time_mutex);
		free(philo->start_time_mutex);
	}

	if (philo->last_meal_mutex) {
		pthread_mutex_destroy(philo->last_meal_mutex);
		free(philo->last_meal_mutex);
	}

	if (philo->state_mutex) {
		pthread_mutex_destroy(philo->state_mutex);
		free(philo->state_mutex);
	}

	if (philo->print_mutex) {
		pthread_mutex_destroy(philo->print_mutex);
		free(philo->print_mutex);
	}
}