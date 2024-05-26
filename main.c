#include "philosophers.h"

int	init_table(t_table *rules, int argc, char *argv[])
{
	rules->num_philosophers = ft_atoi(argv[1]);
	if (!rules->num_philosophers)
		return (0);
	rules->num_forks = rules->num_philosophers;
	rules->time_to_die = ft_atoi(argv[2]);
	if (!rules->time_to_die)
		return (0);
	rules->time_to_eat = ft_atoi(argv[3]);
	if (!rules->time_to_eat)
		return (0);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (!rules->time_to_sleep)
		return (0);
	if (argc == 6)
		rules->num_times_to_eat = ft_atoi(argv[5]);
	else
		rules->num_times_to_eat = -1;
	return (1);
}

void	free_philosophers(t_philo **philosophers, int i)
{
	if (!philosophers)
		return ;
	while (i >= 0)
	{
		if (philosophers[i])
			free(philosophers[i]);
		i--;
	}
	free(philosophers);
}

t_philo	**create_philosophers(t_table *rules)
{
	t_philo	**philosophers;
	int		i;

	philosophers = malloc(sizeof(t_philo *) * rules->num_philosophers);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < rules->num_philosophers)
	{
		philosophers[i] = malloc(sizeof(t_philo));
		if (!philosophers[i])
		{
			free_philosophers(philosophers, i);
			return (NULL);
		}
		philosophers[i]->philo_id = i + 1;
		philosophers[i]->eat_count = 0;
		philosophers[i]->thread_handle = NULL;
		philosophers[i]->thread_attr = NULL;
		i++;
	}
	return (philosophers);
}

void	free_forks(t_fork **forks, int i)
{
	if (!forks)
		return ;
	while (i >= 0)
	{
		if (forks[i])
		{
			pthread_mutex_destroy(&forks[i]->mtx);
			pthread_cond_destroy(&forks[i]->ev);
			free(forks[i]);
		}
		i--;
	}
	free(forks);
}

t_fork	**create_forks(int n)
{
	t_fork	**forks;
	int		i;

	forks = malloc(sizeof(t_fork *) * n);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!forks[i])
		{
			free_forks(forks, i);
			return (NULL);
		}
		forks[i]->spoon_id = i + 1;
		forks[i]->is_used = 0;
		forks[i]->owner = NULL;
		pthread_mutex_init(&forks[i]->mtx, NULL);
		pthread_cond_init(&forks[i]->ev, NULL);
		i++;
	}
	return (forks);
}

int main(int argc, char *argv[])
{
	t_philo	**philosophers;
	t_fork	**forks;
	t_table rules;
	
	if (argc < 5 || argc > 6)
		return (1);
	if(!init_table(&rules, argc, argv))
		return (1);
	philosophers = create_philosophers(&rules);
	if (!philosophers)
		return (1);
	forks = create_forks(rules.num_forks);
	if (!forks)
	{
		free_philosophers(philosophers, rules.num_philosophers - 1);
		return (1);
	}
	free_forks(forks, rules.num_forks - 1);
	return (0);
}