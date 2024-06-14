#include "../inc/philosophers.h"

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	*philo_life(void *philo);

void	eating(t_philo *philo)
{
	philo->last_meal = get_time();
	print_msg(philo, EATING);
	philo->meal_count++;
	if (philo->meal_count >= philo->data->meal_count)
	{
		pthread_mutex_lock(&philo->data->print_mtx);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->data->print_mtx);
	}
	better_sleep(philo->data->time_to_eat );
	drop_forks(philo);
	set_philo_state(philo, SLEEPING);
}

void	sleeping(t_philo *philo)
{
	if (philo->thought_count > 0)
		philo->thought_count = 0;
	print_msg(philo, SLEEPING);
	better_sleep(philo->data->time_to_sleep);
	set_philo_state(philo, THINKING);
}

void	thinking(t_philo *philo)
{
	if (take_forks(philo))
	{
		eating(philo);
		sleeping(philo);
	}
	else if (philo->thought_count == 0)
	{
		philo->thought_count++;
		print_msg(philo, THINKING);
		set_philo_state(philo, THINKING);
		better_sleep(1000);
	}
}

int is_simulation_over(t_philo *p)
{
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
	set_philo_state(p, INACTIVE);
	while (42)
	{
		if (is_dead(p))
			break;
		if (is_everyone_full(p->data) && p->data->meal_count != -1)
			break;
		if (take_forks(p))
		{
			eating(p);
			sleeping(p);
		}
		else
			set_philo_state(p, THINKING);
		if (p->state == THINKING)
			thinking(p);
	}
	print_eat_count(p);
	return (NULL);
}
