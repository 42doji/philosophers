#include "../inc/philosophers.h"

int     main(int argc, char *argv[])
{
	t_data  data;

	static pthread_mutex_t mutex;

	mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data.mutex = mutex;
	if (!parser(argc, argv, &data))
		return (1);
	if (!init_datas(&data))
		return (1);
	start_simulation(&data);
	return (0);
}
