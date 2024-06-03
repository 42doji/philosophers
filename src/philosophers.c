#include "../inc/philosophers.h"

int	parser(int argc, char *argv[], t_data *data)
{
	if (argc < 5 || argc > 6)
		return (0);
	data->philo_count = ft_atoi(argv[1]);
	printf("philo_count: %d\n", data->philo_count);
	data->time_to_die = ft_atoi(argv[2]);
	printf("time_to_die: %d\n", data->time_to_die);
	data->time_to_eat = ft_atoi(argv[3]);
	printf("time_to_eat: %d\n", data->time_to_eat);
	data->time_to_sleep = ft_atoi(argv[4]);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	data->meal_count = -1;
	if (argc == 6)
		data->meal_count = ft_atoi(argv[5]);
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
	// 3.
	// 3. create threads for each philosopher to run
		// 3.1 create thread
		// 3.2 create thread attributes
		// 3.3 create thread callback function
		// 3.4 create thread callback function argument
		// 3.5 create thread
		// 3.6 destroy thread attributes
		// 3.7 destroy thread
	// 4. join threads for each philosopher to finish
		// 4.1 join thread
		// 4.2 destroy thread attributes
		// 4.3 destroy thread
	// 5. free data
		// 5.1 free mutexes
		// 5.2 free philosophers
		// 5.3 free shared data
	// 6. return

	return (0);
}
