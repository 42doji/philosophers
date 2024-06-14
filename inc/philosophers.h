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

// TODO: Add mutexes for each variable in the t_philosopher struct
typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	t_data			*data;
	e_state			state;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t *state_mutex;
	int				meal_count;
	pthread_mutex_t *meal_count_mutex;
	int 			is_full;
	pthread_mutex_t *is_full_mutex;
	int 			thought_count;
	pthread_mutex_t *thought_count_mutex;
	long 			start_time;
	pthread_mutex_t *start_time_mutex;
	long			last_meal;
	pthread_mutex_t *last_meal_mutex;
	pthread_mutex_t *print_mutex;
}	t_philo;

typedef struct s_data
{
	t_philo			*phils;
	t_fork			*forks;
	int				nb_phil;
	pthread_mutex_t *nb_phil_mutex;
	int				time_to_die;
	pthread_mutex_t *time_to_die_mutex;
	int				time_to_eat;
	pthread_mutex_t *time_to_eat_mutex;
	int				time_to_sleep;
	pthread_mutex_t *time_to_sleep_mutex;
	int				meal_count;
	pthread_mutex_t *meal_count_mutex;
	int 			fulled_philo_count;
	pthread_mutex_t *all_ate_mutex;
	int 			everyone_ate;
	pthread_mutex_t	*everyone_ate_mtx;
	int 			someone_is_dead;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t *print_mutex;
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
void				*philo_life(void *philo);
void				dead(t_philo *philo);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				eating(t_philo *philo);
void    			start_simulation(t_data *data);
int					set_philo_state(t_philo *philo, e_state state);
int 				is_dead(t_philo *philo);
int 				is_everyone_full(t_data *data);
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
int					is_simulation_over(t_philo *p);
int 				is_infinite_meals(t_data *data);
void				init_philo_mutexes(t_philo *philo);
void				free_philo_mutexes(t_philo *philo);


#endif
