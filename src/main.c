#include "../inc/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!parser(argc, argv, &data))
		return (1);
	if (!init_datas(&data))
		return (1);
	if (is_infinite_meals(&data))
		infinite_simulation(&data);
	else
		finite_simulation(&data);
	clean_datas(&data);
	return (0);
}
