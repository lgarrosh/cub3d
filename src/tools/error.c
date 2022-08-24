#include "cub.h"

void 	*error(int fd, char *error, int _return)
{
	write(fd, error, ft_strlen(error));
	if (!_return)
		return(NULL);
	return((void *)&_return);
}