/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:13:26 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/14 12:01:54 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

static long long	ft_atol(char *nptr)
{
	int			p;
	int			i;
	long long	res;

	p = 1;
	i = 0;
	res = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			p = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((p < 0 && - res == LLONG_MIN / 10 && nptr[i] > '8')
			|| (p > 0 && res == LLONG_MAX / 10 && nptr[i] > '7'))
		{
			res = res * 10 + (nptr[i++] - '0');
			if (p == 1)
				return (-1);
			return (0);
		}
		res = res * 10 + (nptr[i++] - '0');
	}
	return ((long long)(res * p));
}

int	parse_exit_code(unsigned long long *res, char *str)
{
	int			i;
	long long	tmp;

	i = 0;
	if (!str)
	{
		if (res)
			*res = 2;
		return (1);
	}
	if (!ft_isdigit(str[0]) && str[0] != '+' && str[0] != '-')
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	tmp = ft_atol(str);
	if ((tmp == -1 || tmp == 0) && str[1])
		return (0);
	if (res)
		*res = tmp;
	return (1);
}

void	transform_code(unsigned long long *code)
{
	while (*code > 255)
		*code %= 256;
}

t_env	*get_new_node(char *content)
{
	t_env	*res;

	res = ft_calloc(1, sizeof(t_env));
	if (!res)
		return (NULL);
	res->name = ft_strdup("?");
	res->content = ft_strdup(content);
	if (!res->name || !res->content)
		return (destroy(res));
	return (res);
}

int	exit_builtin(t_list *cmd, t_env **env)
{
	unsigned long long		code;
	t_env					*node;

	code = 0;
	if (cmd->flags)
	{
		if (!parse_exit_code(&code, cmd->flags[0]))
		{
			node = get_new_node(cmd->flags[0]);
			if (!node)
				exit_code(12, env, 0, NULL);
			else
				add_back(env, node, 0);
			return (-2);
		}
		if (cmd->flags[1])
		{
			ft_putstr_fd("exit\nExit: Too many arguments\n", 2);
			exit_code(1, env, 0, NULL);
			return (1);
		}
	}
	transform_code(&code);
	exit_code(code, env, 0, NULL);
	return (-2);
}
