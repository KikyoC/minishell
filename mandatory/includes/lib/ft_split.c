/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:02:37 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/15 15:54:10 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	free_all(char **t)
{
	char	**tmp;

	tmp = t;
	while (*t)
		free(*t++);
	free(tmp);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	fill(char *t, const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
}

static int	set_sub(const char *s, char c, char **t)
{
	int	j;
	int	sub;

	sub = 0;
	j = 0;
	while (s[sub])
	{
		j = 0;
		while (s[sub + j] && s[sub + j] != c)
			j++;
		if (j > 0)
		{
			*t = malloc((j + 1) * sizeof(char));
			if (!*t)
				return (0);
			fill(*t, (s + sub), c);
			sub += j;
			t++;
		}
		else
			sub++;
	}
	*t = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**t;
	int		words;
	int		result;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	t = malloc((words + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	result = set_sub(s, c, t);
	if (!result)
	{
		free_all(t);
		return (NULL);
	}
	return (t);
}
