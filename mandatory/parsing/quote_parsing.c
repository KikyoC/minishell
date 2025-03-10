/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:49:26 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/10 13:49:27 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

int	parse_quote(char *line)
{
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	while (line[i])
	{
		if (line[i] == quote)
			quote = '\0';
		else if ((line[i] == '\'' || line[i] == '"') && !quote)
			quote = line[i];
		i++;
	}
	return (quote);
}
