/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:27:40 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/15 15:53:07 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check(char const s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

static int	trim(char const *s1, char const *set, char *ptr)
{
	int	len;
	int	i;
	int	count;

	count = 0;
	len = ft_strlen(s1);
	i = 0;
	while (check(s1[i], set))
		i++;
	while (check(s1[len - 1], set))
		len--;
	while (i < len)
	{
		if (ptr)
			ptr[count] = s1[i];
		count++;
		i++;
	}
	if (ptr)
		ptr[count] = '\0';
	return (count + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*c;

	if (!s1 || !set)
		return (NULL);
	len = trim(s1, set, NULL);
	c = malloc(len * sizeof(char));
	trim(s1, set, c);
	return (c);
}
