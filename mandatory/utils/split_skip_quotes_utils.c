/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_skip_quotes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:03:02 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:03:03 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

t_list	*check_until(char *line, int *j, char ch, char op)
{
	t_list	*node;
	int		i;
	char	*str;

	i = 0;
	while ((line[i] == op || line[i] == ch) && line[i])
		i++;
	str = ft_calloc(i + 1, sizeof(char));
	*j += i;
	while (--i >= 0)
		str[i] = line[i];
	node = ft_lstnew(str);
	return (node);
}
