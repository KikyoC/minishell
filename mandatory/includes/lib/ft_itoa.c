/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:30:58 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/14 10:43:47 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	recur(unsigned int n, char *ptr, int l)
{
	int	len;

	len = 0;
	if (ptr)
		ptr[l--] = '\0';
	while (n >= 10)
	{
		if (ptr)
			ptr[l--] = (char)((n % 10) + '0');
		n /= 10;
		len++;
	}
	if (ptr)
		ptr[l] = (char)((n % 10) + '0');
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	int				len;
	char			*t;
	int				sign;

	sign = 0;
	if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	num = (unsigned int) n;
	len = recur(num, NULL, 0) + sign;
	t = malloc((len + 2) * sizeof(char));
	if (!t)
		return (NULL);
	if (sign)
		t[0] = '-';
	if (!t)
		return (NULL);
	recur(num, t, len + 1);
	return (t);
}
