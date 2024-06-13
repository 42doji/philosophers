/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyengsan.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:21:09 by doji              #+#    #+#             */
/*   Updated: 2024/06/12 20:24:52 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	*philo_life(void *philo);

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time();
	philo->death_time = philo->last_meal + philo->data->time_to_die;
	philo->meal_count++;
	if (philo->meal_count >= philo->data->meal_count)
	{
		pthread_mutex_lock(&philo->data->mutex);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->data->mutex);
		set_philo_state(philo, FULL);
	}
	pthread_mutex_unlock(&philo->mutex);
	better_sleep(philo->data->time_to_eat);
	drop_forks(philo);
	print_msg(philo, EATING);
	if (philo->meal_count < philo->data->meal_count)
		set_philo_state(philo, SLEEPING);
}

void	sleeping(t_philo *philo)
{
	if (philo->thought_count > 0)
		philo->thought_count = 0;
	print_msg(philo, SLEEPING);
	better_sleep(philo->data->time_to_sleep);
	set_philo_state(philo, THINKING);
}

void	thinking(t_philo *philo)
{
	if (take_forks(philo))
	{
		eating(philo);
		sleeping(philo);
	}
	else if (philo->thought_count == 0)
	{
		philo->thought_count++;
		print_msg(philo, THINKING);
		set_philo_state(philo, THINKING);
		better_sleep(1);
	}
}

void	philo_idle(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->data->philo_created++;
	pthread_mutex_unlock(&philo->mutex);
	while (1)
	{
		if (philo->start_signal)
			break ;
		usleep(100);
	}
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	philo_idle(p);
	set_philo_state(p, INACTIVE);
	while (p->data->finished_simulation == 0)
	{
		if (p->state == DEAD || p->data->everyone_is_full)
			break ;
		if (p->state == EATING && take_forks(p))
		{
			eating(p);
			sleeping(p);
		}
		else
			set_philo_state(p, THINKING);
		if (p->state == THINKING)
			thinking(p);
		if (p->meal_count >= p->data->meal_count && p->data->meal_count != -1)
		{
			set_philo_state(p, FULL);
			break ;
		}
	}
	print_eat_count(p);
	return (NULL);
}
