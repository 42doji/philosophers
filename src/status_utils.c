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
	if (get_time() - philo->last_meal > get_time_to_die(philo->data))
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
	pthread_mutex_lock(data->print_mutex);
	while (i < data->nb_phil)
	{
		if (!data->phils[i].is_full)
		{
			everyone_full = 0;
			break;
		}
		i++;
	}
	data->fulled_philo_count = everyone_full;
	pthread_mutex_unlock(data->print_mutex);
	return (everyone_full);
}

int set_philo_state(t_philo *p, e_state state)
{
	pthread_mutex_lock(p->data->print_mutex);
	if (state == INACTIVE)
	{
		p->start_time = get_time();
		p->last_meal = p->start_time;
		p->state = EATING;
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
		pthread_mutex_unlock(p->data->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(p->data->print_mutex);
	return (1);
}
