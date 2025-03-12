/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:10:46 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:13:10 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

int	pre_exe_final_if(t_list *cmd, char **envp, int state)
{
	if (cmd->input < 0 || cmd->output < 0
		|| (get_builtin(cmd) && !is_pipe(cmd)))
	{
		ft_free_split(envp);
		close_node(cmd);
		return (-1 - (state == -2));
	}
	return (0);
}

int	pre_execute(t_list *cmd, char **envp, t_env **env)
{
	int	state;

	state = 0;
	if (cmd->type != 1)
	{
		ft_free_split(envp);
		return (-3);
	}
	if (cmd->input < 0 || cmd->output < 0)
		exit_code(127, env, 0, NULL);
	if (get_builtin(cmd) != NULL && !is_pipe(cmd)
		&& cmd->input >= 0 && cmd->output >= 0)
	{
		if (ft_strncmp(cmd->command, "exit", 5))
			exit_code(exec_builtin(cmd,
					get_builtin(cmd), 0, env), env, 0, NULL);
		else
			state = exit_builtin(cmd, env);
	}
	return (pre_exe_final_if(cmd, envp, state));
}
