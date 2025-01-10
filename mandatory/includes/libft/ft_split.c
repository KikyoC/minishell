/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:02:37 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/10 14:50:40 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_words(char *str, char *splitter)
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
#include <stdio.h>

char	*get_word(char *str, char *splitter, int *i)
{
	size_t	s_count;

	i = 0;
	printf("%i\n", *i);
	while (str[(*i)])
	{
		if (str[*i] == splitter[0])
		{
			s_count = 0;
			while (str[*i + s_count] && str[*i + s_count] == splitter[s_count])
				s_count++;
			if (s_count == ft_strlen(splitter))
				break;			
		}
		(*i)++;
	}
	return (ft_substr(str, 0, *i));
}


char	**ft_split(char *str, char *splitter)
{
	int		words;
	int		str_index;
	char	**split;
	int		i;

	words = count_words(str, splitter);
	str_index = 0;
	split = ft_calloc(words + 1, sizeof(char *));
	i = 1;
	printf("%s\n", get_word(str, splitter, &i));
	
	return (NULL);
}
