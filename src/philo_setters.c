#include "../inc/philosophers.h"

long	get_start_time(t_philo *philo);
long	get_last_meal(t_philo *philo);
void	add_meal_count(t_philo *philo);
void	add_thought_count(t_philo *philo);
void	minus_thought_count(t_philo *philo);
void	set_philo_is_full(t_philo *philo);

void	set_start_time(t_philo *philo)
{
	pthread_mutex_lock(philo->start_time_mutex);
	philo->start_time = get_time();
	pthread_mutex_unlock(philo->start_time_mutex);
}

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->last_meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->last_meal_mutex);
	if (get_state(philo) == INACTIVE)
	{
		pthread_mutex_lock(philo->last_meal_mutex);
		philo->last_meal_time = get_start_time(philo);
		pthread_mutex_unlock(philo->last_meal_mutex);
	}
}

void	add_meal_count(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_count_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(philo->meal_count_mutex);
}

void	add_thought_count(t_philo *philo)
{
	pthread_mutex_lock(philo->thought_count_mutex);
	philo->thought_count = 1;
	pthread_mutex_unlock(philo->thought_count_mutex);
}

void	minus_thought_count(t_philo *philo)
{
	pthread_mutex_lock(philo->thought_count_mutex);
	philo->thought_count = 0;
	pthread_mutex_unlock(philo->thought_count_mutex);
}

void	set_philo_is_full(t_philo *philo)
{
	pthread_mutex_lock(philo->is_full_mutex);
	philo->is_full = 1;
	pthread_mutex_unlock(philo->is_full_mutex);
}
void	set_philo_state(t_philo *philo, e_state state)
{
	pthread_mutex_lock(philo->state_mutex);
	philo->state = state;
	pthread_mutex_unlock(philo->state_mutex);
}

void	init_philo_state(t_philo *philo, e_state state)
{
	if (state == INACTIVE)
	{
		set_start_time(philo);
		set_last_meal(philo);
		set_philo_state(philo, EATING);
	}
	else
		set_philo_state(philo, state);
}
