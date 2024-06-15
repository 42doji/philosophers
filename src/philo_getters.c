#include "../inc/philosophers.h"

e_state	get_state(t_philo *philo);
int		get_philo_eat_count(t_philo *philo);
int		is_full(t_philo *philo);
int		get_thought_count(t_philo *philo);
long	get_start_time(t_philo *philo);
long	get_last_meal(t_philo *philo);


e_state get_state(t_philo *philo)
{
	e_state state;

	pthread_mutex_lock(philo->data->print_mutex);
	state = philo->state;
	pthread_mutex_unlock(philo->data->print_mutex);
	return (state);
}

int get_philo_eat_count(t_philo *philo)
{
	int eat_count;

	pthread_mutex_lock(philo->data->print_mutex);
	eat_count = philo->meal_count;
	pthread_mutex_unlock(philo->data->print_mutex);
	return (eat_count);
}

int is_full(t_philo *philo)
{
	int is_full;

	pthread_mutex_lock(philo->data->print_mutex);
	is_full = philo->is_full;
	pthread_mutex_unlock(philo->data->print_mutex);
	return (is_full);
}

int get_thought_count(t_philo *philo)
{
	int thought_count;

	pthread_mutex_lock(philo->data->print_mutex);
	thought_count = philo->thought_count;
	pthread_mutex_unlock(philo->data->print_mutex);
	return (thought_count);
}

long	get_start_time(t_philo *philo)
{
	long start_time;

	pthread_mutex_lock(philo->data->print_mutex);
	start_time = philo->start_time;
	pthread_mutex_unlock(philo->data->print_mutex);
	return (start_time);
}

long	get_last_meal(t_philo *philo)
{
	long last_meal;

	pthread_mutex_lock(philo->data->print_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(philo->data->print_mutex);
	return (last_meal);
}