/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:54:07 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 22:54:10 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	status_handler(t_philo *philos, char method, bool new_val)
{
	bool	status;

	status = new_val;
	pthread_mutex_lock(&philos->data->status_mutex);
	if (method == 'g')
		status = philos->data->status;
	else if (method == 's')
		philos->data->status = new_val;
	pthread_mutex_unlock(&philos->data->status_mutex);
	return (status);
}

long long	last_meal_handler(t_philo *philos, char handle, long long new_val)
{
	long long	meal;

	meal = new_val;
	pthread_mutex_lock(&philos->meal_mutex);
	if (handle == 'g')
		meal = philos->last_meal;
	else if (handle == 's')
		philos->last_meal = new_val;
	pthread_mutex_unlock(&philos->meal_mutex);
	return (meal);
}

int	meal_count_handler(t_philo *philos, char handle, int new_val)
{
	int	meal;

	meal = new_val;
	if (handle == 'g')
	{
		pthread_mutex_lock(&philos->data->total_eat_mutex);
		meal = philos->data->total_eat_count;
		pthread_mutex_unlock(&philos->data->total_eat_mutex);
	}
	else if (handle == 's')
	{
		pthread_mutex_lock(&philos->data->total_eat_mutex);
		philos->data->total_eat_count-- ;
		pthread_mutex_unlock(&philos->data->total_eat_mutex);
	}
	return (meal);
}
