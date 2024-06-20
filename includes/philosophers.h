/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:53:32 by doji              #+#    #+#             */
/*   Updated: 2024/06/20 22:53:39 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define LEFT_FORK "has taken a fork"
# define RIGHT_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_error
{
	char			*msg;
	int				status;
}					t_error;

typedef struct s_data
{
	int				nb_phil;
	long long		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				total_eat_count;
	bool			status;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	total_eat_mutex;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	time_mutex;
}					t_data;

typedef struct s_fork
{
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
}					t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	t_fork			fork;
	t_data			*data;
	int				idx;
	int				eat_count;
	long long		last_meal;
	void			*next;
	pthread_mutex_t	meal_mutex;
}					t_philo;

void				error_handler(t_error *error, char *msg, int exit_status);
t_philo				*parser(int argc, char **argv);
void				monitor(t_philo *p, t_philo *head);
void				join_threads(t_philo *philo);
int					sleeping(long long time, t_philo *philos);
void				*routine(void *philo);
int					actions(t_philo *philos, char *action);
int					take_forks(pthread_mutex_t *right, pthread_mutex_t *left);
int					drop_forks(t_philo *philo);
int					eating(t_philo *philo);
bool				status_handler(t_philo *ps, char method, bool val);
long long			last_meal_handler(t_philo *ps, char handle, long long val);
int					meal_count_handler(t_philo *ps, char handle, int val);
long long			get_time(void);
int					ft_usleep(t_philo *philo);
#endif
