#ifndef __PHILOSOPHERS_H__
#define __PHILOSOPHERS_H__
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philosopher t_philo;
typedef struct s_data t_data;
typedef struct time
{
	long int		sec;
	long int		usec;
}	t_tv;

typedef enum t_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	INACTIVE
}	t_state;

typedef struct s_fork
{
	int				id;
	int 			is_taken;
	t_philo 		*owner;
	pthread_mutex_t	mutex;

}	t_fork;

typedef struct s_philosopher
{
	int				id;
	int				meal_count;
	pthread_t		thread;
	t_fork	*first_fork;
	t_fork	*second_fork;
	char			*msg;
	t_tv			last_meal;
	t_state			state;
	t_data			*data;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	t_philo			*philosophers;
	t_fork			*forks;
}	t_data;

/* parsing utils */
int	parser(int argc, char *argv[], t_data *data);

char    		**ft_split(char const *s, char c);
int     		ft_atoi(const char *nptr);
int   	 		ft_count_words(char const *s, char sep);
void	   		ft_allocate(char **tab, char const *s, char sep);
char    		*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_isspace(char c);
int				ft_strlcpy(char *dst, const char *src, int size);
ssize_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);

/* parsing utils */


/* init utils */
int 			init_datas(t_data *data);

int 			init_forks(t_data *data);
int 			init_philos(t_data *data);
/* init utils */

/* free utils */
int 	free_mutexes(t_data *data, int i);
void	clean_philos(t_data *data);
void	clean_forks(t_data *data);
void	free_forks(t_data *data, int i);

/* free utils */

#endif
