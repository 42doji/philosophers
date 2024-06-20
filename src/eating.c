/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:08:49 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:08:50 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void     unlock_mutexes(int left_fork, int right_fork, int w, t_philo **philo)
{
	if (right_fork)
		pthread_mutex_unlock((*philo)->right_fork);
	if (left_fork)
		pthread_mutex_unlock((*philo)->l_fork);
	if (w)
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

static int      is_even(t_philo **philo)
{
	pthread_mutex_lock((*philo)->right_fork);
	if (if_waited_to_long(&(*philo)))
		return (unlock_mutexes(0, 1, 0, &(*philo)), 1);
	pthread_mutex_lock((*philo)->write);
	if (if_waited_to_long(&(*philo)))
		return (unlock_mutexes(0, 1, 1, &(*philo)), 1);
	pthread_mutex_lock(&(*philo)->lock);
	(*philo)->status = 4;
	pthread_mutex_unlock(&(*philo)->lock);
	if (messages((*philo)->status, &(*philo)))
		return (unlock_mutexes(0, 1, 1, &(*philo)), 1);
	pthread_mutex_unlock((*philo)->write);
	pthread_mutex_lock((*philo)->l_fork);
	if (if_waited_to_long(&(*philo)))
		return (unlock_mutexes(1, 1, 0, &(*philo)), 1);
	if (eating(&(*philo)))
		return (1);
	return (0);
}

static int      is_odd(t_philo **philo)
{
	pthread_mutex_lock((*philo)->l_fork);
	if (if_waited_to_long(&(*philo)))
		return (unlock_mutexes(1, 0, 0, &(*philo)), 1);
	pthread_mutex_lock((*philo)->write);
	if (if_waited_to_long(&(*philo)))
		return (unlock_mutexes(1, 0, 1, &(*philo)), 1);
	pthread_mutex_lock(&(*philo)->lock);
	(*philo)->status = 4;
	pthread_mutex_unlock(&(*philo)->lock);
	if (messages((*philo)->status, &(*philo)))
		return (unlock_mutexes(1, 0, 1, &(*philo)), 1);
	pthread_mutex_unlock((*philo)->write);
	if ((*philo)->right_fork == NULL)
		return (unlock_mutexes(1, 0, 0, &(*philo)), 1);
	pthread_mutex_lock((*philo)->right_fork);
	if (if_waited_to_long(&(*philo)))
		return (unlock_mutexes(1, 1, 0, &(*philo)), 1);
	if (eating(&(*philo)))
		return (1);
	return (0);
}

int     is_eating(t_philo **philo)
{
	if (((*philo)->philo_id % 2) == 0)
		return (is_even(&(*philo)));
	else
		return (is_odd(&(*philo)));
}
