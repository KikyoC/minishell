/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:01:39 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/22 17:40:44 by xray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

int	strings(char *input, char *command)
{
	int	i;

	i = 0;
	while ((input[i] && command[i]) && (input[i] == command[i]))
		i++;
	if (input[i] == '\n' && command[i] == '\0')
		return (1);
	return (0);
}

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
	return(join);
}
