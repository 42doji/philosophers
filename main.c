#include "philosophers.h"

void	free_philosophers(t_philo **philosophers, int i)
{
	if (!philosophers)
		return ;
	while (i >= 0)
	{
		free(philosophers[i]->thread_handle);
		free(philosophers[i]);
		i--;
	}
	free(philosophers);
}

t_philo	*create_a_philosopher(int id)
{
	t_philo	*philosopher;

	philosopher = malloc(sizeof(t_philo));
	if (!philosopher)
		return (NULL);
	philosopher->thread_handle = malloc(sizeof(pthread_t));
	if (!philosopher->thread_handle)
	{
		free(philosopher);
		return (NULL);
	}
	philosopher->philo_id = id + 1;
	philosopher->eat_count = 0;
	return (philosopher);
}

t_philo	**create_philosophers(int argc, char *argv[])
{
	t_philo	**philosophers;
	int		i;

	philosophers = malloc(sizeof(t_philo *) * (argc - 1));
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < argc - 1)
	{
		philosophers[i] = malloc(sizeof(t_philo));
		if (!philosophers[i])
		{
			free_philosophers(philosophers, i);
			return (NULL);
		}
		philosophers[i] = create_a_philosopher(i);
		if (!philosophers[i])
		{
			free_philosophers(philosophers, i);
			return (NULL);
		}
		i++;
	}
	return (philosophers);
}



int main(int argc, char *argv[])
{
	t_philo	**philosophers;
	t_fork	**forks;

	if (argc < 5 || argc > 6)
		return (1);

	return (0);
}