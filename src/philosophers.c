#include "../inc/philosophers.h"

void	start_simulation(t_data *data)
{
	int i;

	i = 0;
	if (data->meal_count == 0)
		return ;
	else if (data->nb_phil == 1)
	{
		// TODO
	}
	else
	{
		while (i < data->nb_phil)
		{
			philo_life(&data->phils[i]);
			i++;
		}
	}
}

void	check_process_status(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->data->nb_phil)
	{
		set_philo_state(&philo[i]);
		i++;
	}
}

int	parser(int argc, char *argv[], t_data *data)
{
	if (argc < 5 || argc > 6)
		return (0);
	data->nb_phil = ft_atoi(argv[1]);
	printf("philo_count: %d\n", data->nb_phil);
	data->time_to_die = ft_atoi(argv[2]);
	printf("time_to_die: %d\n", data->time_to_die);
	data->time_to_eat = ft_atoi(argv[3]);
	printf("time_to_eat: %d\n", data->time_to_eat);
	data->time_to_sleep = ft_atoi(argv[4]);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	data->meal_count = -1;
	if (argc == 6)
	{
		data->meal_count = ft_atoi(argv[5]);
		printf("meal_count: %d\n", data->meal_count);
	}
	else
		printf("meal_count: 0\n");
	return (1);
}

int main(int argc, char *argv[])
{
	t_data	data;

	/* 1. parse arguments */
	if (!parser(argc, argv, &data))
		return (1);
	/* 2. initialize data and mutexes for each philosopher */
	if (!init_datas(&data))
		return (1);
	check_process_status(data.phils);
	start_simulation(&data);


	return (0);
}
