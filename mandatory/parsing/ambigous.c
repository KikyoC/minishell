/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambigous.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:51:12 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/10 13:51:13 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

int	ambigous(char *content, int i)
{
	int	count;

	count = 0;
	if (content[0] == '\0')
		return (1);
	while (content[i])
	{
		if (is_operator(content[i], ' ', 0))
			count = 1;
		else
			if (count)
				return (1);
		i++;
	}
	return (0);
}

int	handle_ambigous(t_env *env, t_list **cmds)
{
	t_list	*curr;
	char	*word;
	int		i;

	curr = *cmds;
	i = 0;
	while (curr)
	{
		if (curr->type == REDIRECT)
		{
			if (curr->next && curr->next->been_expanded)
			{
				word = (char *)curr->next->content;
				while (is_operator(word[i], ' ', 0))
					i++;
				if (ambigous((char *)curr->next->content, i))
					return (exit_code(1, &env, 1, curr->next));
			}
		}
		curr = curr->next;
	}
	return (1);
}
