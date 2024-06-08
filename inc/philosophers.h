#ifndef __PHILOSOPHERS_H__
#define __PHILOSOPHERS_H__
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philosopher t_philo;
typedef struct s_data t_data;

typedef enum t_state
{
	THINKING,
	FORK_TAKEN,
	EATING,
	FORK_DROPPED,
	SLEEPING,
	DEAD,
	INACTIVE
}	e_state;  // TODO: rename e_state to e_state

typedef struct s_fork
{
	int				id;
	int 			is_taken;
	pthread_mutex_t	mutex;

}	t_fork;

typedef struct s_philosopher
{
	int				id;
	int				meal_count;
	long 			start_time;
	long			death_time;
	long			last_meal;
	pthread_t		thread;
	t_fork			*first_fork;
	t_fork			*second_fork;
	e_state			state;
	t_data			*data;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t print_mutex;
}	t_philo;

typedef struct s_data
{
	int				nb_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	t_philo			*phils;
	t_fork			*forks;
}	t_data;

/* parsing utils */
int				parser(int argc, char *argv[], t_data *data);
int     		ft_atoi(const char *nptr);
int				ft_isspace(char c);
/* parsing utils */

/* init utils */
int 			init_datas(t_data *data);
int 			init_forks(t_data *data);
int 			init_philos(t_data *data);

/* init utils */

/* free utils */
// TODO: finish
int 			free_mutexes(t_data *data, int i);
void			clean_philos(t_data *data);
void			clean_forks(t_data *data);
void			free_forks(t_data *data, int i);
/* free utils */

/* time utils */
long			get_time(void);
/* time utils */

/* fork funcs */
int	take_forks(t_philo *philo);
int	drop_forks(t_philo *philo);
t_fork	*get_first_fork(t_philo *philo);
t_fork	*get_second_fork(t_philo *philo);
/* fork funcs */

/* routine funcs */
void	*philo_life(void *philo);
void	dead(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
void	print_msg(t_philo *philo, int state);
int set_philo_state(t_philo *philo, e_state state);
void 	print_msg(t_philo *philo, int state);

/* routine funcs */
#endif
