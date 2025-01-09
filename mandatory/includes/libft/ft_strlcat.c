/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:48:52 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/17 12:29:28 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if ((!dst && size == 0) || (!src && size == 0))
		return (0);
	while (*dst && i < size)
	{
		dst++;
		i++;
	}
	while (*src && size > i + 1)
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	if (size > i)
		*dst = '\0';
	while (*src)
	{
		src++;
		i++;
	}
	return (i);
}
