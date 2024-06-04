#include "../inc/philosophers.h"

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

void print_msg(t_philo *philo, int state)
{
	pthread_mutex_lock(&print_mutex);
	if (state == EATING)
		printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id);
	else if (state == DEAD)
		printf("%ld %d died\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(&print_mutex);
}

void eating(t_philo *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (philo->data->meal_count != -1 && philo->meal_count >= philo->data->meal_count)
		return;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	print_msg(philo, EATING);
	philo->meal_count++;
	p->start_time = get_time();
	p->death_time = p->start_time + ((t_philo *)philo)->data->time_to_die;
	usleep(philo->data->time_to_eat * 1000);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->meal_mutex);
	drop_forks(philo);
}

void sleeping(t_philo *philo)
{
	print_msg(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
	philo->state = THINKING;
}

void thinking(t_philo *philo)
{
	philo->state = EATING;
}

void dead(t_philo *philo)
{
	print_msg(philo, DEAD);
}

int check_meal_count(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_phil)
	{
		if (data->meal_count != -1 && data->phils[i].meal_count < data->meal_count)
			return 0;
		i++;
	}
	return 1;
}

int set_philo_state(t_philo *philo)
{
	if (philo->data->meal_count != -1 && philo->meal_count >= philo->data->meal_count)
		return 0;
	if (philo->state == INACTIVE)
	{
		philo->last_meal = get_time();
		philo->state = EATING;
	}
	return 1;
}

void *philo_life(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	p->start_time = get_time();
	p->death_time = p->start_time + ((t_philo *)philo)->data->time_to_die;
	while (1)
	{
		if (check_meal_count(p->data))
			break;
		if (get_time() > p->death_time)
		{
			dead((t_philo *)philo);
			break;
		}
		else if (take_forks((t_philo *)philo))
		{

			eating((t_philo *)philo);
			sleeping((t_philo *)philo);
		}
		else
		{
			thinking((t_philo *)philo);
		}
	}
	return NULL;
}
