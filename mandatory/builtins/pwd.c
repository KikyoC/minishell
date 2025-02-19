/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:53:08 by togauthi          #+#    #+#             */
/*   Updated: 2025/02/14 14:08:20 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

char	*pwd_from_env(t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strncmp(node->name, "PWD", 4) == 0)
			return (ft_strdup(node->content));
		node = node->next;
	}
	return (NULL);
}

/* pwd:
*	Print the current path 
*/
int	pwd(t_list *cmd, t_env **env)
{
	char	*location;

	location = getcwd(NULL, PATH_MAX);
	if (!location)
		location = pwd_from_env(env);
	ft_putstr_fd(location, cmd->output);
	ft_putchar_fd('\n', cmd->output);
	free(location);
	return (0);
}
