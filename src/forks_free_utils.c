/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyengsan.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:20:58 by doji              #+#    #+#             */
/*   Updated: 2024/06/12 18:20:58 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	clean_forks(t_data *data);
void	free_forks(t_data *data, int i);

void clean_forks(t_data *data)
{
	int i;

	if (!data)
		return ;
	i = 0;
	while (i < data->nb_phil)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	free_forks(t_data *data, int i)
{
	if (!data || i < 0)
		return ;
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		data->forks[i].id = -1;
		data->forks[i].is_taken = 0;
		i--;
	}
	free(data->forks);
}
