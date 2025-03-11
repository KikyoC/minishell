/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:01:39 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 17:18:20 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

char	*ft_charjoin(char *str, char ch)
{
	char	*join;
	int		i;

	i = -1;
	if (!str)
	{
		join = ft_calloc(2, sizeof(char));
		if (!join)
			return (NULL);
		join[0] = ch;
		return (join);
	}
	join = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	if (!join)
		return (NULL);
	while (str[++i])
		join[i] = str[i];
	join[i] = ch;
	free(str);
	return (join);
}

void	skip_spaces(char *line, int *i)
{
	while ((line[*i + 1] == ' ' || line[*i + 1] == '\t') && line[*i + 1])
		(*i)++;
}

char	reverse_quote(char quote)
{
	if (quote == '\'')
		return ('"');
	else
		return ('\'');
}
