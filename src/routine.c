/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:09:05 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:09:05 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static t_data   *set_start(t_data *data)
{
	int	index;

	if (!data->start_time)
	{
		data->start_time = get_current_time();
		index = -1;
		while (++index < data->philo_num)
		{
			pthread_mutex_lock(&data->philos[index].lock);
			data->philos[index].last_meal = data->start_time;
			data->philos[index].start_time = data->start_time;
			data->philos[index].status = 1;
			pthread_mutex_unlock(&data->philos[index].lock);
		}
		return (data);
	}
	return (NULL);
}

static int	check_finished(t_data **data, int finished, int number)
{
	int	index;

	if ((*data)->dead || (*data)->finished == (*data)->philo_num)
	{
		index = 0;
		while (index < (*data)->philo_num)
		{
			pthread_mutex_lock(&(*data)->philos[index].lock);
			(*data)->philos[index].status = -1;
			pthread_mutex_unlock(&(*data)->philos[index].lock);
			index++;
		}
		if (finished == 0)
		{
			pthread_mutex_lock(&(*data)->write);
			printf("%zu %d died\n", get_current_time() - (*data)->start_time,
				   (*data)->philos[number].philo_id);
			pthread_mutex_unlock(&(*data)->write);
		}
		return (1);
	}
	return (0);
}

static void	monitoring(t_data **data, int index)
{
	while (1)
	{
		pthread_mutex_lock(&(*data)->philos[index].lock);
		if ((*data)->philos[index].status == -1)
			(*data)->dead = 1;
		pthread_mutex_unlock(&(*data)->philos[index].lock);
		if ((*data)->dead || (*data)->finished == (*data)->philo_num)
			if (check_finished(data, (*data)->finished, index))
				break ;
		pthread_mutex_lock(&(*data)->philos[index].lock);
		if ((get_current_time() - (*data)->philos[index].last_meal)
			>= (*data)->death_time)
		{
			(*data)->dead = 1;
			pthread_mutex_unlock(&(*data)->philos[index].lock);
			check_finished(data, (*data)->finished, index);
			break ;
		}
		if (!(*data)->dead
			&& (*data)->philos[index].eat_count >= (*data)->meals_nr)
			(*data)->finished++;
		pthread_mutex_unlock(&(*data)->philos[index].lock);
		finished_eating(&(*data), &index);
		index++;
	}
}

static void	*checker_routine(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		if (data->start == 1)
		{
			pthread_mutex_unlock(&data->lock);
			break ;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(500);
	}
	data = set_start(data);
	if (data != NULL)
		monitoring(&data, 0);
	return (NULL);
}

int	init_thread(t_data *data)
{
	int	index;

	if (pthread_create(data->supervisor, NULL, checker_routine, data) != 0)
		return (error_handler("thread create failed", data));
	index = -1;
	while (++index < data->philo_num)
	{
		if (pthread_create(data->philos[index].thrd, NULL, philo_routine,
						   &data->philos[index]) != 0)
			return (error_handler("philo thread create failed", data));
	}
	pthread_mutex_lock(&data->lock);
	data->start = 1;
	pthread_mutex_unlock(&data->lock);
	if (pthread_join(*data->supervisor, NULL) != 0)
		return (error_handler("thread_join", data));
	index = -1;
	while (++index < data->philo_num)
		pthread_join(*data->philos[index].thrd, NULL);
	return (0);
}
