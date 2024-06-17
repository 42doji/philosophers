#include "../inc/philosophers.h"

void	dead(t_philo *philo);
int		is_dead(t_philo *philo);
void	set_one_dead(t_data *data);
int		is_someone_dead(t_data *data);

void	dead(t_philo *philo)
{
	print_msg(philo, DEAD);
	set_philo_state(philo, DEAD);
	philo->is_dead = 1;
	set_one_dead(philo->data);
}

int		is_dead(t_philo *philo)
{

	if (get_time() - get_last_meal(philo) > get_time_to_die(philo->data))
	{
		dead(philo);
		return (1);
	}
	return (0);
}

void set_one_dead(t_data *data)
{
	pthread_mutex_lock(data->dead_mutex);
	data->someone_is_dead = 1;
	pthread_mutex_unlock(data->dead_mutex);
}

int is_someone_dead(t_data *data)
{
	int someone_is_dead;

	pthread_mutex_lock(data->dead_mutex);
	someone_is_dead = data->someone_is_dead;
	pthread_mutex_unlock(data->dead_mutex);
	return (someone_is_dead);
}