/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyengsan.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:21:02 by doji              #+#    #+#             */
/*   Updated: 2024/06/12 18:21:03 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!parser(argc, argv, &data))
		return (1);
	if (!init_datas(&data))
		return (1);
	start_simulation(&data);
	create_monitor_thread(&data);
	clean_datas(&data);
	return (0);
}
