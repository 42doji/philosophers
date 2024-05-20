#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "libft/libft.h"

int	main(int argc, char *argv[])
{
	printf("main: Pause.\n");
	pause();
	return (0);
}
