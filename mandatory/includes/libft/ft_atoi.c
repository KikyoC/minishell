/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:17:28 by togauthi          #+#    #+#             */
/*   Updated: 2025/03/12 09:17:36 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		p;
	int		i;
	long	res;

	p = 1;
	i = 0;
	res = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			p = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (res > (LLONG_MAX - (nptr[i] - '0')) / 10)
		{
			if (p == 1)
				return (-1);
			else
				return (0);
		}
		res = res * 10 + (nptr[i++] - '0');
	}
	return ((int)(res * p));
}
