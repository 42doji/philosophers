/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <doji@student.42gyengsan.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:20:45 by doji              #+#    #+#             */
/*   Updated: 2024/06/12 18:20:48 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philosopher	t_philo;
typedef struct s_data			t_data;

typedef enum t_state
{
	THINKING,
	FORK_TAKEN,
	EATING,
	FORK_DROPPED,
	SLEEPING,
	DEAD,
	INACTIVE,
	FULL
}	t_state;

typedef enum t_error
{
	NO_ERROR,
	ARG_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR,
	MUTEX_ERROR
}	t_error;

typedef struct s_fork
{
	int				id;
	int				is_taken;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int				id;
	int				is_full;
	int				meal_count;
	int				thought_count;
	long			start_time;
	long			death_time;
	long			last_meal;
	pthread_t		thread;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_state			state;
	t_data			*data;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_data
{
	int				nb_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	int				everyone_is_full;
	pthread_mutex_t	mutex;
	pthread_t 		monitor_thread;
	t_philo			*phils;
	t_fork			*forks;
}	t_data;

int					parser(int argc, char *argv[], t_data *data);
int					ft_atoi(const char *nptr);
int					ft_isspace(char c);
int					init_datas(t_data *data);
int					init_forks(t_data *data);
int					init_philos(t_data *data);
void				clean_philos(t_data *data);
void				clean_forks(t_data *data);
void				free_forks(t_data *data, int i);
long				get_time(void);
void				better_sleep(long time);
int					take_forks(t_philo *philo);
int					drop_forks(t_philo *philo);
t_fork				*get_first_fork(t_philo *philo);
t_fork				*get_second_fork(t_philo *philo);
void				*philo_life(void *philo);
void				dead(t_philo *philo);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				eating(t_philo *philo);
void				start_simulation(t_data *data);
int					set_philo_state(t_philo *philo, t_state state);
int					is_dead(t_philo *philo);
int					is_everyone_full(t_data *data);
void				print_msg(t_philo *philo, int state);
void				print_eat_count(t_philo *philo);
void				clean_datas(t_data *data);
int					error_handler(t_data *data, t_error error);
int					is_someone_dead(t_data *data);
void 				*monitoring(void *arg);
void				create_monitor_thread(void *data);
void 				check_all_philos_full(t_data *data);

#endif
