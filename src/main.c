#include "../inc/philosophers.h"

int     main(int argc, char *argv[])
{
	t_data  data;

	if (!parser(argc, argv, &data))
		return (1);
	if (!init_datas(&data))
		return (1);
	if (is_infinite_meals(&data))
		start_simulation1(&data);
	else
		start_simulation2(&data);
	clean_datas(&data);
	return (0);
}
