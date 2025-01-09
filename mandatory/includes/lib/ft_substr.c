/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:43:23 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/15 17:00:03 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*t;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		t = malloc(1);
		if (!t)
			return (NULL);
		t[0] = '\0';
		return (t);
	}
	i = 0;
	while (s[i + start] != '\0' && i < len)
		i++;
	t = malloc((i + 1) * sizeof(char));
	if (!t)
		return (NULL);
	ft_memcpy(t, s + start, i);
	t[i] = '\0';
	return (t);
}
