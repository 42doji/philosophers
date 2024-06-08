#include "../inc/philosophers.h"

void print_msg(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (state == EATING)
		printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);
	else if (state == DEAD)
		printf("%ld %d died\n", get_time() - philo->start_time, philo->id);
	else if (state == FORK_TAKEN)
		printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
	else if (state == FORK_DROPPED)
		printf("%ld %d has dropped a fork\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->mutex);
}

int is_everyone_full(t_data *data)
{
	int i;
	int everyone_full = 1;

	pthread_mutex_lock(&data->mutex);
	for (i = 0; i < data->nb_phil; i++)
	{
		if (!data->phils[i].is_full)
		{
			everyone_full = 0;
			break;
		}
	}
	data->everyone_is_full = everyone_full;
	pthread_mutex_unlock(&data->mutex);
	return everyone_full;
}


void eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->death_time = philo->last_meal + philo->data->time_to_die;
	print_msg(philo, EATING);
	philo->meal_count++;
	if (philo->meal_count >= philo->data->meal_count)
		philo->is_full = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	drop_forks(philo);
	philo->state = SLEEPING;
}

void sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
	set_philo_state(philo, THINKING);
}

void thinking(t_philo *philo)
{
	while (philo->state == THINKING)
	{
		if (take_forks(philo))
		{
			eating(philo);
			sleeping(philo);
		}
		else
			usleep(100);
	}
}

void dead(t_philo *philo)
{
	print_msg(philo, DEAD);
	set_philo_state(philo, DEAD);
}

int set_philo_state(t_philo *p, e_state state)
{
	if (state == INACTIVE)
	{
		p->start_time = get_time();
		p->last_meal = p->start_time;
		p->death_time = p->start_time + ((t_philo *)p)->data->time_to_die;
		p->state = INACTIVE;
	}
	else if (state == THINKING)
		p->state = THINKING;
	else if (state == EATING)
		p->state = EATING;
	else if (state == SLEEPING)
		p->state = SLEEPING;
	else if (state == DEAD)
		p->state = DEAD;
	else
		return (0);
	return (1);
}

int is_dead(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		dead(philo);
		return (1);
	}
	return (0);
}

void	print_eat_count(t_philo *philo)
{
	printf("%d philo ate %d times\n", philo->id, philo->meal_count);
}

void	set_philo_is_full(t_philo *philo)
{
	if (philo->meal_count >= philo->data->meal_count)
	{
		pthread_mutex_lock(&philo->data->mutex);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->data->mutex);
	}
	else
		philo->is_full = 0;
}

void *philo_life(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	set_philo_state(p, INACTIVE);
	while (!is_everyone_full(p->data))
	{
		if (is_dead((t_philo *)philo))
			break;
		if (take_forks((t_philo *)philo))
		{

			eating((t_philo *)philo);
			sleeping((t_philo *)philo);
		}
		else
			set_philo_state((t_philo *)philo, THINKING);
		if (p->state == THINKING)
			thinking((t_philo *)philo);
	}
	print_eat_count((t_philo *)philo);
	return NULL;
}
