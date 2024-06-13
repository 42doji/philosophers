/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyengsan.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:20:49 by doji              #+#    #+#             */
/*   Updated: 2024/06/12 18:20:50 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	better_sleep(long time);

void	better_sleep(long time)
{
	long	start;

	if (time <= 0)
		return ;
	start = get_time();
	while (get_time() - start < time)
		usleep(10);
}
