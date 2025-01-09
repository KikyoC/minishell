/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:04:01 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/10 15:40:32 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*txt;
	unsigned char	*txt2;

	txt = (unsigned char *)s1;
	txt2 = (unsigned char *)s2;
	i = 0;
	while (n > i)
	{
		if (txt[i] != txt2[i])
			return (txt[i] - txt2[i]);
		i++;
	}
	return (0);
}
