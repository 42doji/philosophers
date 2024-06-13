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
		if (get_time() - d->phils[i].last_meal > d->time_to_die)
		{
			pthread_mutex_lock(&d->mutex);
			printf("%ld %d died\n", \
			get_time() - d->phils[i].start_time, d->phils[i].id);
			pthread_mutex_unlock(&d->mutex);
			set_philo_state(&d->phils[i], DEAD);
			return (1);
		}
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
	if (full_count == data->nb_phil)
		data->everyone_is_full = 1;
}

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	start_simulation(data);
	while (1)
	{
		if (is_someone_dead(data))
			break ;
		check_all_philos_full(data);
		if (data->everyone_is_full && data->meal_count != -1)
			break ;
		better_sleep(1);
	}
	return (NULL);
}

void	create_monitor_thread(void	*arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_create(&data->monitor_thread, NULL, monitoring, arg);
	pthread_join(data->monitor_thread, NULL);
}
