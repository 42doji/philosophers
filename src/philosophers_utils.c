/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyengsan.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:21:06 by doji              #+#    #+#             */
/*   Updated: 2024/06/12 18:21:07 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	clean_philos(t_data *data);
void	free_forks(t_data *data, int i);
void	clean_datas(t_data *data);
int		init_philos(t_data *data);

void	clean_philos(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < data->nb_phil)
	{
		pthread_mutex_destroy(&data->phils[i].mutex);
		i++;
	}
	free(data->phils);
	data->phils = NULL;
}

void	clean_monitor(t_data *data)
{
	if (!data)
		return ;
	pthread_mutex_destroy(&data->mutex);
}

void clean_datas(t_data *data)
{
	if (!data)
		return ;
	clean_forks(data);
	clean_monitor(data);
	clean_philos(data);
}

int init_philos(t_data *data)
{
	int i;

	data->phils = (t_philo *)calloc(data->nb_phil, sizeof(t_philo));
	if (!data->phils)
		return (0);
	i = 0;
	while (i < data->nb_phil)
	{
		data->phils[i].id = i + 1;
		data->phils[i].meal_count = 0;
		data->phils[i].first_fork = &data->forks[i];
		data->phils[i].second_fork = &data->forks[(i + 1) % data->nb_phil];
		data->phils[i].state = INACTIVE;
		data->phils[i].data = data;
		data->phils[i].is_full = 0;
		data->phils[i].thought_count = 0;
		data->phils[i].start_signal = 0;
		if (pthread_mutex_init(&data->phils[i].mutex, NULL))
		{
			free(data->phils);
			return (0);
		}
		i++;
	}
	return (1);
}


int init_datas(t_data *data)
{
	static pthread_mutex_t mutex;

	mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data->mutex = mutex;
	if (!init_forks(data))
	{
		clean_datas(data);
		return (error_handler(data, MALLOC_ERROR));
	}
	if (!init_philos(data))
	{
		free_forks(data, data->nb_phil - 1);
		clean_datas(data);
		return (error_handler(data, MALLOC_ERROR));
	}
	return (1);
}
