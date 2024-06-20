/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:09:00 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:09:02 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void clean_all(t_data *data)
{
	destroy_philo_mutex(data->philos, data->philo_num);
	destroy_mutexes(data, data->philo_num, 2);
	free_data(data);
}

int     main(int argc, char **argv)
{
	t_data  *data;

	if (!(argc == 5 || argc == 6))
		return (error_handler("Not the right amount of arguments\n", NULL), 1);
	data = malloc (sizeof(t_data));
	if (data == NULL)
		return (1);
	if (init_data(argv, argc == 6, data))
	{
		free(data);
		return (1);
	}
	init_thread(data);
	clean_all(data);
	return (0);
}
