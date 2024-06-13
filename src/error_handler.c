/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyengsan.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:20:52 by doji              #+#    #+#             */
/*   Updated: 2024/06/12 18:20:54 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	error_handler(t_data *data, t_error error);

int	error_handler(t_data *data, t_error error)
{
	if (error == MALLOC_ERROR)
		printf("Error: malloc failed\n");
	else if (error == MUTEX_ERROR)
		printf("Error: mutex failed\n");
	else if (error == THREAD_ERROR)
		printf("Error: thread failed\n");
	else if (error == ARG_ERROR)
		printf("Error: invalid arguments\n");
	if (data)
		clean_datas(data);
	return (0);
}
