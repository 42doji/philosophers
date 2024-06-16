#ifndef __PHILOSOPHERS_H__
#define __PHILOSOPHERS_H__
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philosopher	t_philo;
typedef struct s_data 			t_data;

typedef enum t_state
{
	THINKING,
	FORK_TAKEN,
	EATING,
	FORK_DROPPED,
	SLEEPING,
	DEAD,
	FULL,
	INACTIVE
}	e_state;

typedef enum t_error
{
	ARG_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR,
	MUTEX_ERROR
}	e_error;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	t_data			*data;
	e_state			state;
	t_fork			*first_fork;
	t_fork			*second_fork;
	int				meal_count;
	int 			is_full;
	int 			thought_count;
	long 			start_time;
	long			last_meal_time;
}	t_philo;

typedef struct s_data
{
	t_philo			*phils;
	t_fork			*forks;
	int				nb_phil;
	int				time_to_die;

	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	int 			fulled_philo_count;
	int 			everyone_ate;
	int 			someone_is_dead;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t *print_mutex;
	pthread_mutex_t *nb_phil_mutex;
	pthread_mutex_t	*everyone_ate_mtx;
	pthread_mutex_t *all_ate_mutex;
	pthread_mutex_t *meal_count_mutex;
	pthread_mutex_t *time_to_sleep_mutex;
	pthread_mutex_t *time_to_eat_mutex;
	pthread_mutex_t *time_to_die_mutex;
}	t_data;

int					parser(int argc, char *argv[], t_data *data);
int     			ft_atoi(const char *nptr);
int					ft_isspace(char c);
int 				init_datas(t_data *data);
int 				init_forks(t_data *data);
int 				init_philos(t_data *data);
void				clean_philos(t_data *data);
void				clean_forks(t_data *data);
void				free_forks(t_data *data, int i);
long				get_time(void);
void				better_sleep(long time);
int					take_forks(t_philo *philo);
int					drop_forks(t_philo *philo);
t_fork				*get_first_fork(t_philo *philo);
t_fork				*get_second_fork(t_philo *philo);
void				*philo_life1(void *philo);
void				*philo_life2(void *philo);
void				dead(t_philo *philo);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				eating(t_philo *philo);
void    			start_simulation1(t_data *data);
void    			start_simulation2(t_data *data);
int 				is_dead(t_philo *philo);
void				print_msg(t_philo *philo, int state);
void				print_eat_count(t_philo *philo);
void				clean_datas(t_data *data);
int 				error_handler(t_data *data, e_error error);
void				init_data_mutexes(t_data *data);
void				free_data_mutexes(t_data *data);
void				set_meal_count(t_data *data);
void				set_all_ate(t_data *data);
void				set_dead(t_data *data);
void				init_data_attr(t_data *data);
int					is_someone_dead(t_data *data);
int					is_all_ate(t_data *data);
int					get_meal_count(t_data *data);
int					get_time_to_sleep(t_data *data);
int					get_time_to_eat(t_data *data);
int					get_time_to_die(t_data *data);
int					get_nb_phils(t_data *data);
int					is_simulation_over1(t_philo *p);
int					is_simulation_over2(t_philo *p);
int 				is_infinite_meals(t_data *data);
void				init_philo_mutexes(t_philo *p);
void				free_philo_mutexes(t_philo *philo);

e_state				get_state(t_philo *philo);
int					get_philo_eat_count(t_philo *philo);
int					is_full(t_philo *philo);
int					get_thought_count(t_philo *philo);
long				get_start_time(t_philo *philo);
long				get_last_meal(t_philo *philo);
void	add_meal_count(t_philo *philo);
void	add_thought_count(t_philo *philo);
void	minus_thought_count(t_philo *philo);
void	set_philo_is_full(t_philo *philo);
void	init_philo_state(t_philo *philo, e_state state);
void	set_philo_state(t_philo *philo, e_state state);
int 	get_is_full(t_philo *philo);
void init_philo_mutexes(t_philo *p);
void	set_one_dead(t_data *data);
void	set_last_meal(t_philo *philo);
void	set_start_time(t_philo *philo);
void	allocate_philo_mutexes(t_philo *philo);
void set_philo_mutexes(t_data *data);


#endif
