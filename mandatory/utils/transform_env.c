/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:03:22 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/17 09:27:27 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

char	*special_join(char *s1, char *s2)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(s1, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s2);
	free(tmp);
	return (res);
}

size_t	env_size(t_env **env)
{
	size_t	res;
	t_env	*node;

	node = *env;
	res = 0;
	while (node)
	{
		res++;
		node = node->next;
	}
	return (res);
}

char	**get_envp(t_env **env)
{
	char	**res;
	t_env	*node;
	size_t	i;

	res = ft_calloc(env_size(env) + 1, sizeof(char *));
	if (!res)
	{
		perror("Minishell: ");
		return (NULL);
	}
	node = *env;
	i = 0;
	while (node)
	{
		if (ft_strncmp(node->name, "?", 2))
		{
			res[i] = special_join(node->name, node->content);
			if (!res[i])
				return (ft_free_split(res));
			i++;
		}
		node = node->next;
	}
	return (res);
}
