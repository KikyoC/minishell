/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:13:38 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/12 16:53:44 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

static int	parse(char *str, int *append_mode)
{
	int	i;
	int	part;

	i = 0;
	part = 0;
	*append_mode = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (str[i] != '+' && str[i] != '=' && !ft_isalnum(str[i])
			&& str[i] != '_')
			return (0);
		if (str[i] == '+' && str[i + 1] == '=')
		{
			*append_mode = 1;
			return (1);
		}
		else if (str[i] == '=')
			return (1);
		else if (str[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

static t_env	*assign_node(char *str, int append_mode, t_env **node)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	(*node)->name = ft_substr(str, 0, i - append_mode);
	i += (str[i] != '\0');
	j = i;
	while (str[j])
		j++;
	if (i == j && str[i - 1] == '=')
		(*node)->content = ft_calloc(1, sizeof(char));
	else if (i == j)
		return (destroy_node(*node));
	else
		(*node)->content = ft_substr(str, i, j);
	if (!(*node)->name || (*node)->content == NULL)
		return (destroy_node(*node));
	return (*node);
}

t_env	*new_env(char *str, int append_mode)
{
	t_env	*res;

	res = ft_calloc(1, sizeof(t_env));
	if (!res)
		return (NULL);
	res = assign_node(str, append_mode, &res);
	if (!res)
		return (NULL);
	return (res);
}

void	add_if_required(t_env *e, t_env **env)
{
	t_env	*node;

	node = NULL;
	if (!e)
		return ;
	if (ft_strncmp("PWD", e->name, 4) == 0 && !find_env("OLDPWD", env))
	{
		node = ft_calloc(1, sizeof(t_env));
		if (!node)
			return ;
		node->name = ft_strdup("OLDPWD");
		node->content = ft_strdup(e->content);
	}
	else if (ft_strncmp("OLDPWD", e->name, 7) == 0 && !find_env("PWD", env))
	{
		node = ft_calloc(1, sizeof(t_env));
		if (!node)
			return ;
		node->name = ft_strdup("PWD");
		node->content = ft_strdup(e->content);
	}
	if (node && node->name && node->content)
		add_back(env, node, 0);
	else
		destroy_node(node);
}

int	export(t_list *lst, t_env **env)
{
	int		i;
	int		append_mode;
	t_env	*node;
	int		error;

	i = -1;
	error = 0;
	if (lst->flags == NULL || lst->flags[0] == NULL)
		return (0);
	while (lst->flags[++i])
	{
		if (!parse(lst->flags[i], &append_mode))
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(lst->flags[i], 2);
			ft_putstr_fd(" cannot be parsed\n", 2);
			error = 1;
			continue ;
		}
		node = new_env(lst->flags[i], append_mode);
		add_if_required(node, env);
		add_back(env, node, append_mode);
	}
	return (error);
}
