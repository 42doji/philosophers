/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:54:20 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 22:54:23 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor(t_philo *p, t_philo *head)
{
	bool	status;

	status = true;
	usleep(4000);
	while (status)
	{
		if (get_time() - last_meal_handler(p, 'g', 0) > p->data->time_to_die)
		{
			status_handler(p, 's', false);
			pthread_mutex_lock(&p->data->print_mutex);
			printf("%lld %d %s\n", get_time() - p->data->start_time, p->idx, \
				DIED);
			pthread_mutex_unlock(&p->data->print_mutex);
		}
		p = p->next;
		if (p == NULL)
			p = head;
		status = status_handler(p, 'g', NULL);
	}
}

void	*routine(void *philo)
{
	if (((t_philo *)philo)->idx % 2 == 0)
		ft_usleep((t_philo *) philo);
	while (1)
	{
		if (actions((t_philo *)philo, THINKING) == 1)
			break ;
		if (drop_forks((t_philo *) philo) == 1)
			break ;
		if (eating((t_philo *) philo) == 1)
			break ;
		if (ft_usleep((t_philo *) philo) == 1)
			break ;
	}
	return (NULL);
}
