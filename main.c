#include "philosophers.h"

/*
 * ./philo 5 800 200 200 7
 * 5 philosophers
 * 800 ms to die
 * 200 ms to eat
 * 200 ms to sleep
 * 7 times each philosopher must eat
 */

typedef pthread_mutex_t t_mtx;

typedef struct s_fork
{
	int 	id;
	t_mtx	*mtx;
} t_fork;

typedef struct s_rules
{
	ssize_t	philo_nb;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_to_eat;
} t_rules;

typedef struct s_philo
{
	ssize_t	id;
	ssize_t	meal_count;
	t_fork	*left_fork;
	t_fork	*right_fork;

	t_rules	*rules;
} t_philo;

ssize_t	initialize_table_rules(t_rules *rules, char **argv)
{
	rules->philo_nb = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->nb_to_eat = ft_atoi(argv[5]);
	else
		rules->nb_to_eat = -1;
	return (0);
}



int	main(int argc,char *argv[])
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
		return (1);
	initialize_table_rules(&rules, argv);

	return (0);
}