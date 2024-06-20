/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:09:10 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:09:11 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

size_t  get_current_time(void)
{
	struct timeval  timeval;

	if (gettimeofday(&timeval, NULL) == -1)
		error_handler("gettimeofday() error\n", NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

int     ft_usleep(size_t miliseconds)
{
	size_t  start;

	start = get_current_time();
	while ((get_current_time() - start) < miliseconds)
		usleep(500);
	return (0);
}

int     better_sleep(size_t miliseconds, t_philo *philo)
{
	size_t  start;

	start = get_current_time();
	pthread_mutex_lock(&philo->lock);
	if (philo->status == -1)
	{
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	while ((get_current_time() - start) < miliseconds)
	{
		usleep(500);
		if (((get_current_time() - philo->last_meal)) > philo->time_to_die)
			return (1);
	}
	return (0);
}
