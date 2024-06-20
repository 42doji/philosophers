/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:09:08 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:09:09 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void     unlock_lock(t_philo **philo)
{
	pthread_mutex_unlock(&((*philo)->lock));
}

int     is_sleeping(t_philo **philo)
{
	size_t  time;

	pthread_mutex_lock(&((*philo)->lock));
	if ((*philo)->status == -1)
		return (unlock_lock(&(*philo)), 1);
	if ((*philo)->status != -1)
		(*philo)->status = 2;
	pthread_mutex_unlock(&((*philo)->lock));
	time = get_current_time() - (*philo)->start_time;
	pthread_mutex_lock((*philo)->write);
	printf("%zu %d is sleeping\n", time, (*philo)->philo_id);
	pthread_mutex_unlock((*philo)->write);
	if (better_sleep((*philo)->time_to_sleep, (*philo)))
	{
		pthread_mutex_lock(&((*philo)->lock));
		(*philo)->status = -1;
		return (unlock_lock(&(*philo)), 1);
	}
	else
	{
		pthread_mutex_lock(&((*philo)->lock));
		if ((*philo)->status != -1)
			(*philo)->status = 5;
		return (unlock_lock(&(*philo)), 0);
	}
}
