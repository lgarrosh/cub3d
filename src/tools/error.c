#include "cub.h"

int	ft_error(int fd, char *error, int ret)
{
	write(fd, error, ft_strlen(error));
	return(ret);
}