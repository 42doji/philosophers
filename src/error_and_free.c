/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:08:54 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:08:55 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_philos(t_data *data, int amound)
{
	int	index;

	index = -1;
	if (data->philos != NULL)
	{
		while (++index < amound)
			if (data->philos[index].thrd != NULL)
				free((data->philos[index]).thrd);
		free(data->philos);
	}
}

void	free_data(t_data *data)
{
	if (data->supervisor != NULL)
		free(data->supervisor);
	free_philos(data, data->philo_num);
	if (data->forks != NULL)
		free(data->forks);
	free(data);
}

void	destroy_philo_mutex(t_philo *philo, int number)
{
	int	index;

	index = -1;
	while (++index < number)
		pthread_mutex_destroy(&philo[index].lock);
}

void    destroy_mutexes(t_data *data, int number, int extra)
{
	int	index;

	index = -1;
	while (++index < number)
		pthread_mutex_destroy(&data->forks[index]);
	if (extra >= 1)
		pthread_mutex_destroy(&data->lock);
	if (extra >= 2)
		pthread_mutex_destroy(&data->write);
}

int		error_handler(char *string, t_data *data)
{
	size_t	index;

	index = -1;
	while (string[++index] != '\0')
		write(2, &string[index], 1);
	if (data != NULL)
	{
		destroy_philo_mutex(data->philos, data->philo_num);
		destroy_mutexes(data, data->philo_num, 2);
		free_data(data);
	}
	return (1);
}
