#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_philo	*tmp;

	philo = parser(ac, av);
	if (philo == NULL)
		return (1);
	tmp = philo;
	tmp->data->start_time = get_time();
	while (tmp)
	{
		if ((pthread_create(&tmp->thread, NULL, &routine, tmp)))
			break ;
		tmp = tmp->next;
	}
	tmp = philo;
	monitor(tmp, philo);
	join_threads(philo);
	return (0);
}