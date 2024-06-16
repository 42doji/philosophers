#include "../inc/philosophers.h"

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	*philo_life(void *philo);

void	eating(t_philo *philo)
{
	if (is_dead(philo))
		return ;
	print_msg(philo, EATING);
	set_last_meal(philo);
	add_meal_count(philo);
	is_full(philo);
	better_sleep(get_time_to_eat(philo->data));
	drop_forks(philo);
	set_philo_state(philo, SLEEPING);
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
		usleep(100);
	}
	else
	{
		if (take_forks(philo) == 1)
		{
			set_philo_state(philo, EATING);
			eating(philo);
		}
	}
}

int is_simulation_over1(t_philo *p)
{
	if (is_someone_dead(p->data))
		return (1);
	return (0);
}

int is_simulation_over2(t_philo *p)
{
	if (p->is_full == 1)
		return (1);
	if (is_someone_dead(p->data))
		return (1);
	if (is_all_ate(p->data))
		return (1);
	return (0);
}


void	*philo_life1(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	init_philo_state(p, INACTIVE);
	while (!is_simulation_over1(p))
	{
		if (is_dead(p))
			break ;
		if (p->state == EATING)
		{
			take_forks(p);
			eating(p);
			sleeping(p);
		}
		else if (get_state(p) == THINKING)
			thinking(p);
	}
	print_eat_count(p);
	return (NULL);
}

void	*philo_life2(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	init_philo_state(p, INACTIVE);
	while (!is_simulation_over2(p))
	{
		if (is_dead(p))
			break ;
		if (p->state == EATING)
		{
			take_forks(p);
			eating(p);
			sleeping(p);
		}
		else
			set_philo_state(p, THINKING);
		if (get_state(p) == THINKING)
			thinking(p);
	}
	print_eat_count(p);
	return (NULL);
}
