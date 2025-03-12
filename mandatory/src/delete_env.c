/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:06:57 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:06:59 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

void	*destroy_node(t_env *node)
{
	if (!node)
		return (NULL);
	if (node->name)
		free(node->name);
	if (node->content)
		free(node->content);
	free(node);
	return (NULL);
}

void	*destroy(t_env *env)
{
	t_env	*node;
	t_env	*next;

	node = env;
	while (node)
	{
		next = node->next;
		destroy_node(node);
		node = next;
	}
	return (NULL);
}
