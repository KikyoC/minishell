/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:26:59 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/10 18:41:13 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

char	**reformat_all(char **s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[i])
	{
		tmp = ft_strjoin(s[i], "/");
		free(s[i]);
		s[i] = tmp;
		i++;
	}
	return (s);
}

char	**get_paths(char *env)
{
	int		i;
	char	**paths;

	if (!env)
		return (NULL);
	i = 0;
	paths = NULL;
	paths = ft_split(env, ":");
	if (!paths)
		return (paths);
	paths = reformat_all(paths);
	return (paths);
}

char	*does_exist(char *cmd, char **paths)
{
	char	*join;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	if (!paths)
		return (NULL);
	if (!(*paths))
		return (NULL);
	while (paths[i])
	{
		join = ft_strjoin(paths[i], cmd);
		if (!access(join, X_OK))
			return (join);
		free(join);
		i++;
	}
	return (NULL);
}
