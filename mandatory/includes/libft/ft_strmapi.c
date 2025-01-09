/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:31:08 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/15 15:54:33 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*t;
	unsigned int	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	t = malloc((len + 1) * sizeof(char));
	i = 0;
	if (!t)
		return (NULL);
	while (i < len)
	{
		t[i] = (*f)(i, s[i]);
		i++;
	}
	t[i] = '\0';
	return (t);
}
