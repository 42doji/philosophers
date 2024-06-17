#include "../inc/philosophers.h"

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	*infinite_routine(void *philo);
void	*finite_routine(void *philo);
int is_simulation_over1(t_philo *p);
int is_simulation_over2(t_philo *p);


void	eating_inf(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	print_msg(philo, EATING);
	set_last_meal(philo);
	better_sleep(get_time_to_eat(philo->data));
	drop_forks(philo);
	if (get_thought_count(philo) > 0)
		minus_thought_count(philo);
	set_philo_state(philo, SLEEPING);
}

void	eating(t_philo *philo)
{
	print_msg(philo, EATING);
	set_last_meal(philo);
	add_meal_count(philo);
	is_full(philo);
	better_sleep(get_time_to_eat(philo->data));
	drop_forks(philo);
	if (get_thought_count(philo) > 0)
		minus_thought_count(philo);
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	better_sleep(get_time_to_sleep(philo->data));
	set_philo_state(philo, THINKING);
}

void	thinking(t_philo *philo)
{
	if (philo->thought_count == 0)
	{
		print_msg(philo, THINKING);
		philo->thought_count = 1;
	}
	else
		set_philo_state(philo, EATING);
}

int is_simulation_over1(t_philo *p)
{
	if (is_someone_dead(p->data))
		return (1);
	if (p->state == INACTIVE)
		init_philo_state(p, INACTIVE);
	return (0);
}

int is_simulation_over2(t_philo *p)
{
	if (is_someone_dead(p->data))
		return (1);
	if (is_everyone_ate(p->data))
		return (1);
	return (0);
}

void	*infinite_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (!is_simulation_over1(p))
	{
		if (p->state == DEAD)
			break ;
		else if (p->state == EATING)
		{
			take_forks(p);
			eating_inf(p);
			sleeping(p);
		}
		if (p->state == THINKING)
			thinking(p);
	}
	print_eat_count(p);
	return (NULL);
}

void	*finite_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	init_philo_state(p, INACTIVE);
	while (!is_simulation_over2(p))
	{
		if (is_dead(p))
			break ;
		if (take_forks(p))
		{
			eating(p);
			sleeping(p);
		}
		thinking(p);
		if (p->is_full == 1 || p->is_dead == 1)
			break ;
	}
	print_eat_count(p);
	return (NULL);
}
