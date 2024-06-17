#include "../inc/philosophers.h"

int get_nb_phils(t_data *data);
int get_time_to_die(t_data *data);
int get_time_to_eat(t_data *data);
int get_time_to_sleep(t_data *data);
int get_meal_count(t_data *data);
int is_infinite_meals(t_data *data);


int get_nb_phils(t_data *data)
{
	int nb_phils;

	nb_phils = 0;
	pthread_mutex_lock(data->nb_phil_mutex);
	nb_phils = data->nb_phil;
	pthread_mutex_unlock(data->nb_phil_mutex);
	return (nb_phils);
}

int get_time_to_die(t_data *data)
{
	int time_to_die;

	time_to_die = 0;
	pthread_mutex_lock(data->time_to_die_mutex);
	time_to_die = data->time_to_die;
	pthread_mutex_unlock(data->time_to_die_mutex);
	return (time_to_die);
}

int get_time_to_eat(t_data *data)
{
	int time_to_eat;

	time_to_eat = 0;
	pthread_mutex_lock(data->time_to_eat_mutex);
	time_to_eat = data->time_to_eat;
	pthread_mutex_unlock(data->time_to_eat_mutex);
	return (time_to_eat);
}

int get_time_to_sleep(t_data *data)
{
	int time_to_sleep;

	time_to_sleep = 0;
	pthread_mutex_lock(data->time_to_sleep_mutex);
	time_to_sleep = data->time_to_sleep;
	pthread_mutex_unlock(data->time_to_sleep_mutex);
	return (time_to_sleep);
}

int get_meal_count(t_data *data)
{
	int meal_count;

	meal_count = 0;
	pthread_mutex_lock(data->meal_count_mutex);
	meal_count = data->meal_count;
	pthread_mutex_unlock(data->meal_count_mutex);
	return (meal_count);
}




int is_infinite_meals(t_data *data)
{
	int meal_count;

	meal_count = 0;
	pthread_mutex_lock(data->meal_count_mutex);
	meal_count = data->meal_count;
	pthread_mutex_unlock(data->meal_count_mutex);
	if (meal_count == -1)
		return (1);
	return (0);
}
