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

	pthread_mutex_lock(philo->state_mutex);
	state = philo->state;
	pthread_mutex_unlock(philo->state_mutex);
	return (state);
}

int get_philo_eat_count(t_philo *philo)
{
	int eat_count;

	pthread_mutex_lock(philo->meal_count_mutex);
	eat_count = philo->meal_count;
	pthread_mutex_unlock(philo->meal_count_mutex);
	return (eat_count);
}

int get_is_full(t_philo *philo)
{
	int is_full;

	pthread_mutex_lock(philo->is_full_mutex);
	is_full = philo->is_full;
	pthread_mutex_unlock(philo->is_full_mutex);
	return (is_full);
}

int is_full(t_philo *philo)
{
	int philo_eat_count;
	int	total_eat_count;

	philo_eat_count = get_philo_eat_count(philo);
	total_eat_count = get_meal_count(philo->data);
	if (is_infinite_meals(philo->data))
		return (0);
	else if (philo_eat_count >= total_eat_count)
	{
		set_philo_is_full(philo);
		set_philo_state(philo, FULL);
	}
	return (get_is_full(philo));
}

int get_thought_count(t_philo *philo)
{
	int thought_count;

	pthread_mutex_lock(philo->thought_count_mutex);
	thought_count = philo->thought_count;
	pthread_mutex_unlock(philo->thought_count_mutex);
	return (thought_count);
}

long	get_start_time(t_philo *philo)
{
	long start_time;

	pthread_mutex_lock(philo->start_time_mutex);
	start_time = philo->start_time;
	pthread_mutex_unlock(philo->start_time_mutex);
	return (start_time);
}

long	get_last_meal(t_philo *philo)
{
	long last_meal;

	pthread_mutex_lock(philo->last_meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(philo->last_meal_mutex);
	return (last_meal);
}