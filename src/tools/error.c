#include "cube.h"

int	ft_error(int fd, char *error, int ret)
{
	if (write(fd, error, ft_strlen(error)) > 0)
		return (ret);
	return(-1);
}