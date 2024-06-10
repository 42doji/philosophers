#include "../inc/philosophers.h"

void	dead(t_philo *philo);
int		is_dead(t_philo *philo);
int		is_everyone_full(t_data *data);
int		set_philo_state(t_philo *p, e_state state);

void	dead(t_philo *philo)
{
	print_msg(philo, DEAD);
	set_philo_state(philo, DEAD);
}

int		is_dead(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		dead(philo);
		return (1);
	}
	return (0);
}

int		is_everyone_full(t_data *data)
{
	int	i;
	int	everyone_full;

	i = 0;
	everyone_full = 1;
	pthread_mutex_lock(&data->mutex);
	while (i < data->nb_phil)
	{
		if (!data->phils[i].is_full)
		{
			everyone_full = 0;
			break;
		}
		i++;
	}
	data->everyone_is_full = everyone_full;
	pthread_mutex_unlock(&data->mutex);
	return (everyone_full);
}

int set_philo_state(t_philo *p, e_state state)
{
	pthread_mutex_lock(&p->data->mutex);
	if (state == INACTIVE)
	{
		p->start_time = get_time();
		p->last_meal = p->start_time;
		p->death_time = p->start_time + p->data->time_to_die;
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
	{
		pthread_mutex_unlock(&p->data->mutex);
		return (0);
	}
	pthread_mutex_unlock(&p->data->mutex);
	return (1);
}
