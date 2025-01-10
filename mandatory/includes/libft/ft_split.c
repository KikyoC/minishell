/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:02:37 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/10 17:40:40 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char *str, char *splitter)
{
	int		words;
	int		i;
	size_t	s_count;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == splitter[0])
		{
			s_count = 0;
			while (str[i + s_count] && str[i + s_count] == splitter[s_count])
				s_count++;
			if (s_count == ft_strlen(splitter) && str[i + s_count])
				words++;
		}
		i++;
	}
	words++;
	return (words);
}

int	set_word(char *str, char *splitter, char **to_save)
{
	int		i;
	size_t	s_count;

	i = 0;
	while (str[(i)])
	{
		if (str[i] == splitter[0])
		{
			s_count = 0;
			while (str[i + s_count] && str[i + s_count] == splitter[s_count])
				s_count++;
			if (s_count == ft_strlen(splitter))
				break ;
		}
		(i)++;
	}
	*to_save = ft_substr(str, 0, i);
	return (i + s_count);
}

char	**ft_split(char *str, char *splitter)
{
	int		words;
	int		current_word;
	char	**split;
	int		count;

	words = count_words(str, splitter);
	split = ft_calloc(words + 1, sizeof(char *));
	current_word = 0;
	count = 0;
	while (current_word < words)
	{
		count += set_word(&str[count], splitter, &split[current_word]);
		if (!split[current_word])
			return (ft_free_split(split));
		current_word ++;
	}
	return (split);
}
