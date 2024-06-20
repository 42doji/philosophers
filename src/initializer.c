/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:08:57 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:08:57 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_parsed	*parse_input(char **argv, int flag)
{
	t_parsed	*token;

	token = malloc(sizeof(t_parsed));
	if (token == NULL)
		return (NULL);
	if (ft_atoi(argv[1], &token->amount_of_philo))
		return (free(token), NULL);
	if (ft_atoi(argv[2], &token->time_to_die))
		return (free(token), NULL);
	if (ft_atoi(argv[3], &token->time_to_eat))
		return (free(token), NULL);
	if (ft_atoi(argv[4], &token->time_to_sleep))
		return (free(token), NULL);
	if (flag)
	{
		if (ft_atoi(argv[5], &token->times_eaten))
			return (free(token), NULL);
	}
	else
		token->times_eaten = INT_MAX;
	return (token);
}

static int	set_forks(t_data *data, int amount)
{
	int	index;

	index = -1;
	while (++index < amount)
	{
		if (pthread_mutex_init(&data->forks[index], NULL) != 0)
			return (index);
	}
	return (-1);
}

static int	program(t_parsed *token, t_data *data)
{
	int	forks;

	set_default_data(&data);
	data->supervisor = malloc(sizeof(pthread_t));
	if (data->supervisor == NULL)
		return (free_data(data), 0);
	data->philo_num = token->amount_of_philo;
	data->meals_nr = token->times_eaten;
	data->philos = malloc(sizeof(t_philo) * token->amount_of_philo);
	if (data->philos == NULL)
		return (free_data(data), 0);
	data->death_time = token->time_to_die;
	data->eat_time = token->time_to_eat;
	data->sleep_time = token->time_to_sleep;
	data->forks = malloc(sizeof(pthread_mutex_t) * token->amount_of_philo);
	if (data->forks == NULL)
		return (free_data(data), 0);
	forks = set_forks(data, data->philo_num);
	if (forks != -1)
		return (destroy_mutexes(data, forks, 0), free_data(data), 0);
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (destroy_mutexes(data, data->philo_num, 0), free_data(data), 0);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (destroy_mutexes(data, data->philo_num, 1), free_data(data), 0);
	return (1);
}

static int	set_philos(t_data **data)
{
	int	index;

	index = -1;
	while (++index < (*data)->philo_num)
	{
		set_default_philos(&(*data)->philos[index], &(*data), index);
		(*data)->philos[index].thrd = malloc(sizeof(pthread_t));
		if ((*data)->philos[index].thrd == NULL)
			return (0);
		(*data)->philos[index].philo_id = index + 1;
		(*data)->philos[index].time_to_eat = (*data)->eat_time;
		(*data)->philos[index].time_to_die = (*data)->death_time;
		(*data)->philos[index].time_to_sleep = (*data)->sleep_time;
		if (pthread_mutex_init(&((*data)->philos[index]).lock, NULL) != 0)
			return (destroy_philo_mutex((*data)->philos, index),
					free((*data)->philos[index].thrd), 0);
		(*data)->philos[index].l_fork = &(*data)->forks[index];
		(*data)->philos[index].write = &(*data)->write;
	}
	return (1);
}

int	init_data(char **argv, int is_optional, t_data *data)
{
	t_parsed	*token;

	token = parse_input(argv, is_optional);
	if (token == NULL)
		return (1);
	if (program(token, data) == 0)
		return (1);
	free(token);
	if (set_philos(&data) == 0)
		return (destroy_mutexes(data, data->philo_num, 2), free_data(data), 1);
	return (0);
}
