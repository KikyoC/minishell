/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:42:17 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/17 12:29:20 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int ch)
{
	int		i;
	int		p;
	char	c;

	i = 0;
	c = (char) ch;
	p = -1;
	while (s[i])
	{
		if (s[i] == c)
			p = i;
		i++;
	}
	if (c == s[i])
		return ((char *)s + i);
	if (p < 0)
		return (NULL);
	return ((char *)s + p);
}
