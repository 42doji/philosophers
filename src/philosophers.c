#include "../inc/philosophers.h"

void	start_simulation(t_data *data);
int		parser(int argc, char *argv[], t_data *data);

void    start_simulation(t_data *data)
{
	int i;

	i = 0;
	if (data->meal_count == 0)
		return ;
	else if (data->nb_phil == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("%d 1 died\n", data->time_to_die);
		return ;
	}
	else
	{
		while (i < data->nb_phil)
		{
			pthread_create(&data->phils[i].thread, NULL, philo_life, &data->phils[i]);
			i++;
		}
		i = 0;
		while (i < data->nb_phil)
		{
			pthread_join(data->phils[i].thread, NULL);
			i++;
		}
	}
}

int		parser(int argc, char *argv[], t_data *data)
{
	if (argc < 5 || argc > 6)
		error_handler(data, ARG_ERROR);
	data->nb_phil = ft_atoi(argv[1]);
	printf("philo_count: %d\n", data->nb_phil);
	data->time_to_die = ft_atoi(argv[2]) + 15;
	printf("time_to_die: %d\n", data->time_to_die) ;
	data->time_to_eat = ft_atoi(argv[3]);
	printf("time_to_eat: %d\n", data->time_to_eat);
	data->time_to_sleep = ft_atoi(argv[4]);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	data->meal_count = -1;
	data->everyone_is_full = 0;
	if (argc == 6)
	{
		data->meal_count = ft_atoi(argv[5]);
		printf("meal_count: %d\n", data->meal_count);
	}
	else
		printf("meal_count: 0\n");
	return (1);
}
