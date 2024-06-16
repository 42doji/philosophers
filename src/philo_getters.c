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

	if (get_thought_count(philo) > 0)
		add_thought_count(philo);
	state = philo->state;
	return (state);
}

int get_philo_eat_count(t_philo *philo)
{
	int eat_count;

	eat_count = philo->meal_count;
	return (eat_count);
}

int get_is_full(t_philo *philo)
{
	int is_full;

	is_full = philo->is_full;
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

	thought_count = philo->thought_count;
	return (thought_count);
}

long	get_start_time(t_philo *philo)
{
	long start_time;

	start_time = philo->start_time;
	return (start_time);
}

long	get_last_meal(t_philo *philo)
{
	long last_meal;

	last_meal = philo->last_meal_time;
	return (last_meal);
}