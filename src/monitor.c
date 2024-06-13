/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:29:53 by doji              #+#    #+#             */
/*   Updated: 2024/06/13 10:29:59 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	is_someone_dead(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb_phil)
	{
		if (is_dead(&d->phils[i]))
			return (1);
		i++;
	}
	return (0);
}

void	check_all_philos_full(t_data *data)
{
	int	i;
	int	full_count;

	i = 0;
	full_count = 0;
	while (i < data->nb_phil)
	{
		if (data->phils[i].meal_count >= data->meal_count)
			full_count++;
		i++;
	}
	pthread_mutex_lock(&data->mutex);
	if (full_count == data->nb_phil && data->meal_count != -1)
		data->everyone_is_full = 1;
	pthread_mutex_unlock(&data->mutex);
}

void	monitor_idle(t_data *data)
{
	int i;

	i = 0;
	while (data->philo_created < data->nb_phil)
	{
		usleep(100);
	}
	while (i < data->nb_phil)
	{
		data->phils[i].start_signal = 1;
		i++;
	}
}

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	printf("monitoring start\n");
	monitor_idle(data);
	while (42)
	{
		check_all_philos_full(data);
		if (data->everyone_is_full && data->meal_count != -1)
			break ;
		if (is_someone_dead(data))
			break ;
		usleep(100);
	}
	data->finished_simulation = 1;
	return (NULL);
}
