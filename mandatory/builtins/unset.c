/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:14:02 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:14:33 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

void	remove_env(char *str, t_env **env)
{
	t_env	*node;
	size_t	len;

	node = *env;
	len = ft_strlen(str);
	while (node)
	{
		if (ft_strncmp(node->name, str, len) == 0)
		{
			if (node->prev)
				node->prev->next = node->next;
			if (node->next)
				node->next->prev = node->prev;
			free(node->name);
			free(node->content);
			free(node);
			return ;
		}
		node = node->next;
	}
}

int	unset(t_list *lst, t_env **env)
{
	int	i;

	i = 0;
	while (lst->flags[i])
	{
		remove_env(lst->flags[i], env);
		i++;
	}
	return (0);
}
