/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyengsan.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:21:04 by doji              #+#    #+#             */
/*   Updated: 2024/06/12 18:21:05 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	start_simulation(t_data *data);
int		parser(int argc, char *argv[], t_data *data);

void	start_simulation(t_data *d)
{
	int	i;

	i = 0;
	if (d->nb_phil == 1)
	{
		printf("0 1 has taken a fork\n");
		d->phils[i].start_time = get_time();
		usleep(d->time_to_die * 1000);
	}
	else
	{
		pthread_create(&d->monitor_thread, NULL, monitoring, d);
		while (i < d->nb_phil)
		{
			pthread_create(&d->phils[i].thread, NULL, philo_life, &d->phils[i]);
			i++;
		}
		i = 0;
		while (i < d->nb_phil)
		{
			pthread_join(d->phils[i].thread, NULL);
			i++;
		}
		pthread_join(d->monitor_thread, NULL);
	}
}

int	parser(int argc, char *argv[], t_data *data)
{
	if (argc < 5 || argc > 6)
		return (error_handler(data, ARG_ERROR));
	data->nb_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meal_count = -1;
	data->philo_created = 0;
	data->everyone_is_full = 0;
	data->finished_simulation = 0;
	if (argc == 6)
		data->meal_count = ft_atoi(argv[5]);
	return (1);
}
