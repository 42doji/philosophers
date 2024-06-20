/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:09:03 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:09:03 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int      set_routine(t_philo **philo)
{
	if (((*philo)->philo_id % 2) == 0)
	{
		if (is_eating(&(*philo)))
			return (1);
		if (is_sleeping(&(*philo)))
			return (1);
	}
	else
	{
		if (is_sleeping(&(*philo)))
			return (1);
		if (is_eating(&(*philo)))
			return (1);
	}
	return (0);
}

static int      thinking(t_philo **philo)
{
	long    time;
	size_t  time2;

	pthread_mutex_lock((*philo)->write);
	time2 = get_current_time() - (*philo)->start_time;
	printf("%zu %d is thinking\n", time2, (*philo)->philo_id);
	pthread_mutex_unlock((*philo)->write);
	time = (*philo)->time_to_die - ((*philo)->time_to_eat * 2)
		   - (*philo)->time_to_sleep;
	if (time < 0)
		time = 0;
	if (better_sleep((size_t) time, *philo))
		return (1);
	return (0);
}

static int      check_status(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->lock);
	if ((*philo)->status != -1)
	{
		pthread_mutex_unlock(&(*philo)->lock);
		if (thinking(&(*philo)))
			return (1);
	}
	else
		pthread_mutex_unlock(&(*philo)->lock);
	return (0);
}

static void     set_start(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->lock);
	if ((*philo)->status == 1)
	{
		(*philo)->status = 5;
		pthread_mutex_unlock(&(*philo)->lock);
	}
	else
		pthread_mutex_unlock(&(*philo)->lock);
}

void    *philo_routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->status == -1)
		{
			pthread_mutex_unlock(&philo->lock);
			break ;
		}
		else if (philo->status == 5)
		{
			pthread_mutex_unlock(&philo->lock);
			if (set_routine(&philo))
				break ;
			if (check_status(&philo))
				break ;
		}
		else
			pthread_mutex_unlock(&philo->lock);
		set_start(&philo);
	}
	return (NULL);
}
