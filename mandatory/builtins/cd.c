/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:13:49 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:13:51 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

static t_env	*find(char *str, t_env **env)
{
	t_env	*node;
	size_t	len;

	node = *env;
	len = ft_strlen(str);
	while (node)
	{
		if (ft_strncmp(str, node->name, len) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	*get_home(t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strncmp("HOME", node->name, 4) == 0 && node->content[0])
			return (node->content);
		node = node->next;
	}
	ft_putstr_fd("Minishell: HOME not set\n", 2);
	return (NULL);
}

void	switch_pwd(char *old_path, t_env **env)
{
	t_env	*old;
	t_env	*current;
	char	*current_path;

	old = find("OLDPWD", env);
	current = find("PWD", env);
	if (current)
		current_path = getcwd(NULL, PATH_MAX);
	if (old)
	{
		free(old->content);
		old->content = old_path;
	}
	else
		free(old_path);
	if (current)
	{
		if (!current_path)
			return ;
		free(current->content);
		current->content = current_path;
	}
}

int	cd(t_list *lst, t_env **env)
{
	char	*final;
	char	*old;

	old = getcwd(NULL, PATH_MAX);
	if (lst->flags == NULL || lst->flags[0] == NULL)
		final = get_home(env);
	else if (lst->flags[0] && lst->flags[1])
	{
		ft_putstr_fd(
			"Minishell: Only 1 argument is supported with this function\n", 2);
		return (0);
	}
	else
		final = lst->flags[0];
	if (!final)
		return (1);
	if (chdir(final))
	{
		perror("Minishell");
		free(old);
		return (1);
	}
	switch_pwd(old, env);
	return (0);
}
