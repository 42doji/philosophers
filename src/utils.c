/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:54:24 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 22:54:26 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	len = 0;
	while (s[len++])
		;
	ptr = (char *)malloc(sizeof(char) * (--len + 1));
	if (!ptr)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	error_handler(t_error *error, char *msg, int exit_status)
{
	if (error->status == 0)
	{
		error->msg = ft_strdup(msg);
		error->status = exit_status;
	}
}

void	join_threads(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*prev;

	tmp = philo;
	while (tmp)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
	free(philo->data);
	tmp = philo;
	while (tmp)
	{
		prev = tmp;
		free(prev->fork.right);
		tmp = tmp->next;
		free(prev);
	}
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(t_philo *philo)
{
	if (actions(philo, SLEEPING) == 1)
		return (1);
	if (sleeping(philo->data->time_to_sleep, philo) == 1)
		return (1);
	return (0);
}
