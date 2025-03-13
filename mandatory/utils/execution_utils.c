/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:30:28 by togauthi          #+#    #+#             */
/*   Updated: 2025/03/13 13:30:45 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

pid_t	command_not_found(t_list *cmd, char **envp, t_env **env)
{
	ft_putstr_fd("Minishell: Command not found\n", 2);
	close_node(cmd);
	ft_free_split(envp);
	exit_code(127, env, 0, NULL);
	cmd->mode = 127;
	return (-5);
}
