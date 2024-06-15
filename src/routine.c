#include "../inc/philosophers.h"

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	*philo_life(void *philo);

void	eating(t_philo *philo)
{
	if (is_dead(philo))
	{
		drop_forks(philo);
		set_philo_state(philo, DEAD);
		return ;
	}
	print_msg(philo, EATING);
	set_last_meal(philo);
	add_meal_count(philo);
	better_sleep(get_time_to_eat(philo->data));
	drop_forks(philo);
	is_full(philo);
	set_philo_state(philo, SLEEPING);
}

void	sleeping(t_philo *philo)
{
	if (philo->thought_count > 0)
		philo->thought_count = 0;
	print_msg(philo, SLEEPING);
	better_sleep(get_time_to_sleep(philo->data));
	set_philo_state(philo, THINKING);
}

void	thinking(t_philo *philo)
{
	is_dead(philo);
	if (get_thought_count(philo) == 1)
	{
		set_philo_state(philo, EATING);
		minus_thought_count(philo);
	}
	else if (philo->thought_count == 0)
	{
		add_thought_count(philo);
		print_msg(philo, THINKING);
		set_philo_state(philo, THINKING);
	}
}

int is_simulation_over(t_philo *p)
{
	if (is_dead(p))
		return (1);
	if (is_infinite_meals(p->data) && is_full(p))
		return (1);
	if (is_someone_dead(p->data))
		return (1);
	if (is_all_ate(p->data) && !is_infinite_meals(p->data))
		return (1);
	return (0);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	init_philo_state(p, INACTIVE);
	while (!is_simulation_over(p))
	{
		if (get_state(p) == EATING)
		{
			if (take_forks(p))
				eating(p);
			if (is_full(p))
				break ;
		}
		else
			thinking(p);
		if (get_state(p) == SLEEPING)
			sleeping(p);
	}
	print_eat_count(p);
	return (NULL);
}
