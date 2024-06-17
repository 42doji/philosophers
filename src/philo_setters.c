#include "../inc/philosophers.h"

long	get_start_time(t_philo *philo);
long	get_last_meal(t_philo *philo);
void	add_meal_count(t_philo *philo);
void	add_thought_count(t_philo *philo);
void	minus_thought_count(t_philo *philo);
void	set_philo_is_full(t_philo *philo);

void	set_start_time(t_philo *philo)
{
	philo->start_time = get_time();
}

void	set_last_meal(t_philo *philo)
{
	philo->last_meal_time = get_time();
	if (get_state(philo) == INACTIVE)
	{
		philo->last_meal_time = get_start_time(philo);
	}
}

void	add_meal_count(t_philo *philo)
{
	philo->meal_count++;
}

void	add_thought_count(t_philo *philo)
{
	philo->thought_count = 1;
}

void	minus_thought_count(t_philo *philo)
{
	philo->thought_count = 0;
}

void	set_philo_is_full(t_philo *philo)
{
	philo->is_full = 1;
}
void	set_philo_state(t_philo *philo, e_state state)
{
	philo->state = state;
}

void	init_philo_state(t_philo *philo, e_state state)
{
	if (state == INACTIVE)
	{
		set_start_time(philo);
		set_philo_state(philo, EATING);
		set_last_meal(philo);
	}
	else
		set_philo_state(philo, state);
}
