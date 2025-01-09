/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:29:29 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/14 12:30:27 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	size_t	itf;
	size_t	i;

	itf = 0;
	i = 0;
	if ((size == 0 && !str) || (size == 0 && !to_find))
		return (NULL);
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] && i < size)
	{
		while (str[i + itf] == to_find[itf] && i + itf < size)
		{
			itf++;
			if (itf == ft_strlen(to_find))
				return ((char *)str + i);
		}
		itf = 0;
		i++;
	}
	return (NULL);
}
