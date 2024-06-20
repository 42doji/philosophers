/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:08:52 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:08:53 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void     unlock_mutexes(int left_fork, int right_fork, int write, t_philo **philo)
{
	if (right_fork)
		pthread_mutex_unlock((*philo)->right_fork);
	if (left_fork)
		pthread_mutex_unlock((*philo)->l_fork);
	if (write)
		pthread_mutex_unlock((*philo)->write);
}

static int      if_waited_to_long(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->lock);
	if ((*philo)->status == -1)
	{
		pthread_mutex_unlock(&(*philo)->lock);
		return (1);
	}
	pthread_mutex_unlock(&(*philo)->lock);
	if (((get_current_time() - (*philo)->last_meal)) > (*philo)->time_to_die)
	{
		pthread_mutex_lock(&(*philo)->lock);
		(*philo)->status = -1;
		pthread_mutex_unlock(&(*philo)->lock);
		return (1);
	}
	return (0);
}

int     eating(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->lock);
	if (((*philo)->status != -1))
	{
		(*philo)->status = 3;
		(*philo)->last_meal = get_current_time();
		pthread_mutex_unlock(&(*philo)->lock);
		pthread_mutex_lock((*philo)->write);
		if (if_waited_to_long(&(*philo)))
			return (unlock_mutexes(1, 1, 1, &(*philo)), 1);
		if (messages((*philo)->status, &(*philo)))
			return (unlock_mutexes(1, 1, 1, &(*philo)), 1);
		pthread_mutex_unlock((*philo)->write);
		better_sleep((*philo)->time_to_eat, *philo);
		pthread_mutex_lock(&(*philo)->lock);
		(*philo)->eat_count++;
		if ((*philo)->status != -1)
			(*philo)->status = 5;
		pthread_mutex_unlock(&(*philo)->lock);
	}
	else
		pthread_mutex_unlock(&(*philo)->lock);
	return (unlock_mutexes(1, 1, 0, &(*philo)), 0);
}
