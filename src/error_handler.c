#include "../inc/philosophers.h"

int	error_handler(t_data *data, e_error error)
{
	if (error == MALLOC_ERROR)
		printf("Error: malloc failed\n");
	else if (error == MUTEX_ERROR)
		printf("Error: mutex failed\n");
	else if (error == THREAD_ERROR)
		printf("Error: thread failed\n");
	else if (error == ARG_ERROR)
		printf("Error: invalid arguments\n");
	if (data)
		clean_datas(data);
	return (0);
}