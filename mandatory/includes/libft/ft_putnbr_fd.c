/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:55:46 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/14 10:41:47 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	recur(unsigned int num, int fd)
{
	if (num > 9)
	{
		recur(num / 10, fd);
		recur(num % 10, fd);
	}
	else
		ft_putchar_fd(num + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
	{
		write (fd, "-", 1);
		n *= -1;
	}
	num = (unsigned int)n;
	recur(num, fd);
}
