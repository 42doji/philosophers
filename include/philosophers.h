/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:08:43 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 21:08:44 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>

typedef struct	s_parsed
{
	int	amount_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_eaten;
}	t_parsed;

typedef struct	s_philo
{
	pthread_t	*thrd;
	int			philo_id;
	int			eat_count;
	int			status;
	size_t		start_time;
	size_t		time_to_eat;
	size_t		time_to_die;
	size_t		time_to_sleep;
	size_t		last_meal;
	pthread_mutex_t	lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write;
}	t_philo;

typedef struct s_data
{
	pthread_t	*supervisor;
	int			start;
	int			philo_num;
	int			meals_nr;
	int			dead;
	int			finished;
	t_philo		*philos;
	size_t		death_time;
	size_t		eat_time;
	size_t		sleep_time;
	size_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

int		init_data(char **argv, int is_optional, t_data *data);
size_t	get_current_time(void);
int		ft_usleep(size_t miliseconds);
int		better_sleep(size_t miliseconds, t_philo *philo);
int		ft_atoi(char *nptr, int *nr);
int		messages(int status, t_philo **philo);
void	set_default_data(t_data **data);
void	set_default_philos(t_philo *philo, t_data **data, int index);
int		init_thread(t_data *data);
void    *philo_routine(void *args);
int		error_handler(char *string, t_data *data);
void	destroy_mutexes(t_data *data, int number, int extra);
void	destroy_philo_mutex(t_philo *philo, int number);
void	free_data(t_data *data);
int		is_eating(t_philo **philo);
int		eating(t_philo **philo);
int		is_sleeping(t_philo **philo);
void	finished_eating(t_data **data, int *index);
#endif
