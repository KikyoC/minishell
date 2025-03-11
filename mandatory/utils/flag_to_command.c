/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_to_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:02:47 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:02:49 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

void	flag_to_comand(t_list **cmds)
{
	t_list	*new;

	new = ft_lstnew(ft_strdup((*cmds)->flags[0]));
	new->next = (*cmds)->next;
	new->prev = (*cmds);
	new->command = strdup((*cmds)->flags[0]);
	(*cmds)->next = new;
	(*cmds)->next->prev = new;
	new->flags = split_flags((*cmds)->flags);
	(*cmds)->flags = NULL;
	new->type = 1;
}
