#include "../inc/philosophers.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->death_time = philo->last_meal + philo->data->time_to_die;
	print_msg(philo, EATING);
	philo->meal_count++;
	if (philo->meal_count >= philo->data->meal_count)
	{
		pthread_mutex_lock(&philo->data->mutex);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->data->mutex);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	better_sleep(philo->data->time_to_eat);
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
	} else if (philo->thought_count == 0)
	{
		philo->thought_count++;
		print_msg(philo, THINKING);
		set_philo_state(philo, THINKING);
		better_sleep(1);
	}
}

void	destroy_philosopher(t_philo *p)
{
	if (!p)
		return ;
	p->id = -1;
	p->meal_count = -1;
	p->is_full = 0;
	p->first_fork = NULL;
	p->second_fork = NULL;
	p->state = INACTIVE;
	p->last_meal = -1;
	pthread_mutex_destroy(&p->meal_mutex);
	p->data = NULL;
	pthread_mutex_destroy(&p->meal_mutex);
	free(p->thread);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	set_philo_state(p, INACTIVE);
	while (1)
	{
		if (is_everyone_full(p->data) && p->data->meal_count != -1)
			break;
		if (is_dead(p))
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
