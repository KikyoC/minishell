/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:25:52 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/10 15:48:21 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int ch, size_t n)
{
	size_t			i;
	unsigned char	*txt;
	unsigned char	c;

	c = (char)ch;
	txt = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (txt[i] == c)
			return (txt + i);
		i++;
	}
	return (NULL);
}
