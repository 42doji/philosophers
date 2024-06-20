/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:33:30 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 23:33:32 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_philo	*tmp;

	philo = parser(ac, av);
	if (philo == NULL)
		return (1);
	tmp = philo;
	tmp->data->start_time = get_time();
	while (tmp)
	{
		if ((pthread_create(&tmp->thread, NULL, &routine, tmp)))
			break ;
		tmp = tmp->next;
	}
	tmp = philo;
	init_philos(tmp, philo);
	create_threads(philo);
	return (0);
}
