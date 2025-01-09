/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:22:05 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/16 09:50:20 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	len(size_t *len1, size_t *len2, const char *s1, const char *s2)
{
	*len1 = ft_strlen(s1);
	*len2 = ft_strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*t;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len(&len1, &len2, s1, s2);
	t = malloc(len1 + len2 + 1);
	if (!t)
		return (NULL);
	i = 0;
	while (len1 > i)
	{
		t[i] = s1[i];
		i++;
	}
	while (len2 + len1 > i)
	{
		t[i] = *s2;
		i++;
		s2++;
	}
	t[len2 + len1] = '\0';
	return (t);
}
