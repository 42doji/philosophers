/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:54:15 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 22:54:18 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr, t_error *error)
{
	unsigned long long	res;

	res = 0;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			return (error_handler(error, "negative value\n", 1), 1);
		nptr++;
	}
	while (*nptr && (*nptr) >= '0' && (*nptr) <= '9')
	{
		res = (res * 10) + (*nptr - '0');
		if (res > INT_MAX)
			return (error_handler(error, \
			"int max\n", 1), 1);
		nptr++;
	}
	if (*nptr)
		return (error_handler(error, "not a number\n", 1), 1);
	return (res);
}

t_philo	*init_philo(t_data *env, int i)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->data = env;
	philo->last_meal = get_time();
	philo->idx = i + 1;
	philo->eat_count = 0;
	philo->fork.right = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->fork.right)
		return (free(philo), NULL);
	if (pthread_mutex_init(&philo->meal_mutex, NULL))
		return (free(philo), free(philo->fork.right), NULL);
	if (pthread_mutex_init(philo->fork.right, NULL))
		return (free(philo), free(philo->fork.right), NULL);
	return (philo);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*env;
	t_error	*error;

	env = malloc(sizeof(t_data));
	error = malloc(sizeof(t_error));
	if (!env || !error)
		return (NULL);
	error->status = 0;
	error->msg = NULL;
	env->nb_phil = ft_atoi(av[1], error);
	env->time_to_die = ft_atoi(av[2], error);
	env->time_to_eat = ft_atoi(av[3], error);
	env->time_to_sleep = ft_atoi(av[4], error);
	if (ac == 6)
		env->eat_count = ft_atoi(av[5], error);
	else
		env->eat_count = -1;
	if (error->status == 1)
		return (printf("%s", error->msg), free(error->msg), free(error),
			free(env), NULL);
	if (env->nb_phil > 200 || env->nb_phil < 1 || env->time_to_die < 60
		|| env->time_to_eat < 60 || env->time_to_sleep < 60)
		return (printf("the info it's not correct \n" ), \
						free(error->msg), free(error), free(env), NULL);
	return (free(error->msg), free(error), env);
}

t_philo	*create_philos(t_data *env)
{
	t_philo	*philo;
	t_philo	*head;
	t_philo	*prev;
	int		i;

	prev = NULL;
	head = NULL;
	i = 0;
	while (i < env->nb_phil)
	{
		philo = init_philo(env, i);
		if (philo == NULL)
			return (NULL);
		if (i == 0)
			head = philo;
		else
		{
			prev->next = philo;
			philo->fork.left = prev->fork.right;
		}
		prev = philo;
		i++;
	}
	head->fork.left = prev->fork.right;
	return (prev->next = NULL, head);
}

t_philo	*parser(int argc, char **argv)
{
	t_philo	*philo;
	t_data	*d;

	if (argc != 6 && argc != 5)
		return (printf("wrong input \n" ), NULL);
	d = init_data(argc, argv);
	if (d == NULL || d->eat_count == 0)
		return (NULL);
	d->status = true;
	d->total_eat_count = d->eat_count * d->nb_phil;
	if ((pthread_mutex_init(&d->status_mutex, NULL)))
		return (NULL);
	if ((pthread_mutex_init(&d->time_mutex, NULL)))
		return (NULL);
	if ((pthread_mutex_init(&d->print_mutex, NULL)))
		return (NULL);
	if ((pthread_mutex_init(&d->total_eat_mutex, NULL)))
		return (NULL);
	d->start_time = get_time();
	philo = create_philos(d);
	if (philo == NULL)
		return (free(d), NULL);
	return (philo);
}
