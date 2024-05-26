#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

typedef pthread_mutex_t t_mtx;

typedef struct	s_philosopher
{
	int				philo_id;
	int				eat_count;
	pthread_t		*thread_handle;
	pthread_attr_t	*thread_attr;
}	t_philo;

typedef struct	spoon
{
	int spoon_id;
	int is_used;
	t_philo *owner;
	t_mtx mtx;
	pthread_cond_t ev;
}	t_fork;

typedef struct	s_table
{
	int num_philosophers;
	int num_forks;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_times_to_eat;
}	t_table;

#endif