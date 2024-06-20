/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:09:06 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:09:07 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/philosophers.h"

void    finished_eating(t_data **data, int *index)
{
	int     i;

	if (!(*data)->dead && *index == (*data)->philo_num - 1)
	{
		if ((*data)->finished != (*data)->philo_num)
			(*data)->finished = 0;
		*index = -1;
	}
	if ((*data)->finished == (*data)->philo_num)
	{
		i = 0;
		while (i < (*data)->philo_num)
		{
			pthread_mutex_lock(&(*data)->philos[i].lock);
			(*data)->philos[i].status = -1;
			pthread_mutex_unlock(&(*data)->philos[i].lock);
			i++;
		}
	}
}
