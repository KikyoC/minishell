/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:49:34 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:02:40 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"
#include <string.h>

t_list	*find_command(t_list *cmd)
{
	t_list	*curr;

	curr = cmd;
	while (curr && curr->type != 1)
		curr = curr->prev;
	if (curr)
		return (curr);
	return (NULL);
}

char	**split_flags(char **flags)
{
	int		i;
	int		j;
	char	**cpy;

	i = 0;
	j = 0;
	while (flags[i])
		i++;
	cpy = ft_calloc(i, sizeof(char *));
	if (!cpy)
		return (NULL);
	cpy[i - 1] = NULL;
	while (j < i - 1)
	{
		cpy[j] = ft_strdup(flags[j + 1]);
		j++;
	}
	ft_free_split(flags);
	return (cpy);
}

char	**give_flags(t_list *curr, t_list *cmds)
{
	int		len;
	int		index;
	char	**new;

	index = 0;
	len = split_len(curr->flags) + split_len(cmds->flags);
	new = ft_calloc(len + 1, sizeof(char *));
	new[len] = NULL;
	split_realloc(curr->flags, new, &index);
	curr->flags = NULL;
	split_realloc(cmds->flags, new, &index);
	cmds->flags = NULL;
	return (new);
}

void	modify_flags(t_list **cmds)
{
	t_list	*curr;
	t_list	*new;
	t_list	*tmp;

	curr = find_command(*cmds);
	if (!curr)
	{
		new = ft_lstnew(ft_strdup((*cmds)->flags[0]));
		tmp = (*cmds)->next;
		if ((*cmds)->next)
			(*cmds)->next->prev = new;
		(*cmds)->next = new;
		new->next = tmp;
		new->prev = (*cmds);
		new->command = strdup((*cmds)->flags[0]);
		new->flags = split_flags((*cmds)->flags);
		(*cmds)->flags = NULL;
		new->type = 1;
	}
	else
		curr->flags = give_flags(curr, *cmds);
}

void	file_flags(t_list **cmds)
{
	t_list	*new;
	t_list	*tmp;

	new = ft_lstnew(ft_strdup((*cmds)->flags[0]));
	tmp = (*cmds)->next;
	if ((*cmds)->next)
		(*cmds)->next->prev = new;
	(*cmds)->next = new;
	new->next = tmp;
	new->prev = (*cmds);
	new->command = strdup((*cmds)->flags[0]);
	new->flags = split_flags((*cmds)->flags);
	(*cmds)->flags = NULL;
	new->type = 1;
}
