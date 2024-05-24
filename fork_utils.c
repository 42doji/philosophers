#include "philosophers.h"

void	clean_forks(pthread_mutex_t **forks, ssize_t n)
{
	ssize_t	i;

	if (!forks)
		return ;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
		i++;
	}
	free(forks);
}

void	free_forks(pthread_mutex_t **forks, ssize_t i)
{
	if (!forks)
		return ;
	while (i >= 0)
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
		i--;
	}
	free(forks);
}

pthread_mutex_t	*create_fork(void)
{
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	if (!fork)
		return (NULL);
	if (pthread_mutex_init(fork, NULL))
	{
		free(fork);
		return (NULL);
	}
	return (fork);
}

pthread_mutex_t **create_forks(ssize_t n)
{
	pthread_mutex_t	**forks;
	ssize_t 		i;

	forks = malloc(sizeof(pthread_mutex_t *) * n);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n)
	{
		forks[i] = create_fork();
		if (!forks[i])
		{
			free_forks(forks, i);
			return (NULL);
		}
		i++;
	}
	return (forks);
}