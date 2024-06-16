#include "../inc/philosophers.h"

void	dead(t_philo *philo);
int		is_dead(t_philo *philo);

void	dead(t_philo *philo)
{
	print_msg(philo, DEAD);
	set_philo_state(philo, DEAD);
	set_one_dead(philo->data);
	philo->is_dead = 1;
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


