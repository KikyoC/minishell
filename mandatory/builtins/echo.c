/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:13:43 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:13:44 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

void	write_echo(char **args, t_list *cmd)
{
	int		i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], cmd->output);
		i++;
		if (args[i])
			ft_putchar_fd(' ', cmd->output);
	}
}

int	is_good_skip_line(char *str)
{
	int	i;

	if (!str || !str[0] || !str[1] || str[0] != '-')
		return (0);
	i = 1;
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_list *lst, t_env **env)
{
	int	new_line;

	new_line = 0;
	(void)env;
	if (!lst->flags || !lst->flags[0])
	{
		ft_putchar_fd('\n', lst->output);
		return (0);
	}
	while (is_good_skip_line(lst->flags[new_line]))
		new_line++;
	if (!new_line)
	{
		write_echo(lst->flags, lst);
		ft_putchar_fd('\n', lst->output);
	}
	else
		write_echo(&lst->flags[new_line], lst);
	return (0);
}
