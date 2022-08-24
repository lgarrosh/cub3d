/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:25:35 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/20 15:32:00 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int x, int y)
{
	int	i;

	i = x;
	if (y == 0)
		return (1);
	while (y != 1)
	{
		x *= i;
		y--;
	}
	return (x);
}

static size_t	ft_len(unsigned int n)
{
	size_t			len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t			len;
	unsigned int	i;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		i = n * -1;
	}
	else if (n == 0)
	{
		ft_putchar_fd(48, fd);
		return ;
	}
	else
		i = n;
	len = ft_len(i) - 1;
	while (len + 1)
	{
		ft_putchar_fd(i / ft_pow(10, (int)len) + 48, fd);
		i %= ft_pow(10, (int)len);
		len--;
	}
}
