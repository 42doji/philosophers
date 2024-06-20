/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:09:12 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:09:13 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void    set_default_data(t_data **data)
{
	(*data)->start = 0;
	(*data)->dead = 0;
	(*data)->finished = 0;
	(*data)->start_time = 0;
}

void    set_default_philos(t_philo *philo, t_data **data, int index)
{
	philo->last_meal = 0;
	philo->start_time = 0;
	if (index == (*data)->philo_num - 1)
	{
		if ((*data)->philo_num - 1 != 0)
			(*data)->philos[index].right_fork = &(*data)->forks[0];
		else
			(*data)->philos[index].right_fork = NULL;
	}
	else
		(*data)->philos[index].right_fork = &(*data)->forks[index + 1];
}

static void     printing(size_t time, int id, char *string)
{
	printf("%zu %d %s\n", time, id, string);
}

int     messages(int status, t_philo **philo)
{
	size_t  time;

	time = get_current_time() - (*philo)->start_time;
	if (status == 3)
	{
		if ((*philo)->status != -1)
			return (printing(time, (*philo)->philo_id, "is eating"), 0);
		else
			return (1);
	}
	else if (status == 4)
	{
		pthread_mutex_lock(&(*philo)->lock);
		if ((*philo)->status != -1)
		{
			pthread_mutex_unlock(&(*philo)->lock);
			return (printing(time, (*philo)->philo_id, "has taken a fork"), 0);
		}
		else
		{
			pthread_mutex_unlock(&(*philo)->lock);
			return (1);
		}
	}
	return (0);
}

int     ft_atoi(char *nptr, int *nr)
{
	int             sign;
	long    number;

	number = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		number = number * 10 + (*nptr - '0');
		if (number * sign > INT_MAX || number * sign < INT_MIN)
			return (1);
		nptr++;
	}
	if (number * sign < 1)
		return (1);
	*nr = (int)(number * sign);
	return (0);
}
