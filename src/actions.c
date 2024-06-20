/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:53:51 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 22:54:01 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleeping(long long time, t_philo *philos)
{
	bool		status;
	long long	timer;

	status = true;
	timer = get_time();
	while (status)
	{
		if (get_time() - timer >= time)
			break ;
		status = status_handler(philos, 'g', NULL);
		usleep(50);
	}
	return (0);
}

int	actions(t_philo *philos, char *action)
{
	int	status;

	pthread_mutex_lock(&philos->data->print_mutex);
	if (status_handler(philos, 'g', NULL))
	{
		printf("%lld %d %s\n", get_time() - philos->data->start_time, \
				philos->idx, action);
		status = 0;
	}
	else
		status = 1;
	pthread_mutex_unlock(&philos->data->print_mutex);
	return (status);
}

int	take_forks(pthread_mutex_t *right, pthread_mutex_t *left)
{
	if (right != NULL)
		pthread_mutex_unlock(left);
	if (right != NULL)
		pthread_mutex_unlock(right);
	return (0);
}

int	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork.right);
	if (actions(philo, RIGHT_FORK) == 1)
	{
		pthread_mutex_unlock(philo->fork.right);
		return (1);
	}
	if (philo->data->nb_phil == 1)
	{
		sleeping(philo->data->time_to_die, philo);
		pthread_mutex_unlock(philo->fork.right);
		return (1);
	}
	pthread_mutex_lock(philo->fork.left);
	if (actions(philo, LEFT_FORK) == 1)
	{
		take_forks(philo->fork.right, philo->fork.left);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	last_meal_handler(philo, 's', get_time());
	if (actions(philo, EATING) == 1)
	{
		take_forks(philo->fork.right, philo->fork.left);
		return (1);
	}
	if (sleeping(philo->data->time_to_eat, philo) == 1)
	{
		take_forks(philo->fork.right, philo->fork.left);
		return (1);
	}
	take_forks(philo->fork.right, philo->fork.left);
	if (philo->data->eat_count != -1)
	{
		if (philo->eat_count != philo->data->eat_count)
		{
			philo->eat_count++;
			pthread_mutex_lock(&philo->data->total_eat_mutex);
			philo->data->total_eat_count-- ;
			pthread_mutex_unlock(&philo->data->total_eat_mutex);
		}
	}
	if (meal_count_handler(philo, 'g', 0) == 0)
		status_handler(philo, 's', false);
	return (0);
}
