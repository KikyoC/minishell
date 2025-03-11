/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:13:55 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:13:58 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

int	print_this(t_env *env)
{
	if (ft_strncmp(env->name, "?", 2) == 0)
		return (0);
	return (1);
}

int	aff_env(t_list *lst, t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (print_this(node))
		{
			ft_putstr_fd(node->name, lst->output);
			ft_putchar_fd('=', lst->output);
			if (node->content)
				ft_putstr_fd(node->content, lst->output);
			ft_putchar_fd('\n', lst->output);
		}
		node = node->next;
	}
	return (1);
}
