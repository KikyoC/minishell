/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:47:45 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/12 14:58:37 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

int	triple(t_list *cmds, t_env **env)
{
	t_list	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->type == 1 && curr->command && curr->command[0] == '|')
			return (exit_code(2, env, 2, curr));
		else if (curr->type == 1 && curr->command && curr->command[0] == '<')
			return (exit_code(2, env, 2, curr));
		else if (curr->type == 1 && curr->command && curr->command[0] == '>')
			return (exit_code(2, env, 2, curr));
		curr = curr->next;
	}
	return (1);
}

void	rm_command(t_list *curr)
{
	t_list	*tmp;

	if (!curr->command)
	{
		tmp = curr->next;
		if (curr->next)
			curr->next->prev = curr->prev;
		if (curr->prev)
			curr->prev->next = curr->next;
		ft_lstdelone(curr, free);
		if (tmp)
			curr = tmp->prev;
		else
			curr = tmp;
	}
}

void	remove_null_command(t_list **cmds)
{
	t_list	*curr;

	curr = *cmds;
	while (curr)
	{
		if (curr->type == COMMAND)
		{
			if (*cmds != curr)
				rm_command(curr);
			else
			{
				*cmds = curr->next;
				(*cmds)->prev = NULL;
				ft_lstdelone(curr, free);
				curr = *cmds;
			}
		}
		if (curr)
			curr = curr->next;
	}
}
