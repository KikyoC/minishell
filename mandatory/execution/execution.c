/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:09:57 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/14 15:38:33 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

int	builtin_children(t_list *cmd, t_env **env, char **envp)
{
	exit_code(get_builtin(cmd)(cmd, env), env, 0, NULL);
	close_node(cmd);
	ft_free_split(envp);
	return (1);
}

int	children(t_list *cmd, t_env **env, char **envp, int next)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, handle_sigquit);
	if (next > 2)
		close(next);
	if (get_builtin(cmd))
		return (builtin_children(cmd, env, envp));
	if (cmd->input > 2)
		dup2(cmd->input, 0);
	if (cmd->output > 2)
		dup2(cmd->output, 1);
	close_node(cmd);
	if (cmd->type == 1 && cmd->input >= 0 && cmd->output >= 0 && cmd->mode < 2)
	{
		execve(cmd->command, cmd->flags, envp);
		perror("Execution error");
	}
	ft_free_split(envp);
	if (cmd->type != 1 || cmd->input >= 0 || cmd->output >= 0)
		return (-1);
	return (0);
}

pid_t	execute(t_list *cmd, t_env **env, int next)
{
	pid_t	f;
	char	**envp;

	envp = get_envp(env);
	if (!cmd->command && cmd->type == 1 && cmd->mode < 2)
		return (command_not_found(cmd, envp, env));
	if (!is_pipe(cmd) && get_builtin(cmd) && cmd->input >= 0
		&& cmd->output >= 0)
	{
		exit_code(get_builtin(cmd)(cmd, env), env, 0, NULL);
		close_node(cmd);
		ft_free_split(envp);
		return (- (!ft_strncmp("exit", cmd->command, 5)));
	}
	f = fork();
	if (f < 0)
	{
		perror("Minishell");
		return (0);
	}
	if (f == 0)
		return (children(cmd, env, envp, next));
	close_node(cmd);
	ft_free_split(envp);
	return (f);
}

static void	go_next(t_list **lst, t_env **env, int *next)
{
	*lst = (*lst)->next;
	while (*lst && (*lst)->prev->type != PIPE)
		(*lst) = (*lst)->next;
	prepare_command(lst, env, next);
}

int	run(t_list **lst, t_env **env)
{
	int	next;
	int	code;
	int	*pids;

	next = 0;
	pids = get_pid_list(*lst);
	if (!pids)
		return (12);
	prepare_command(lst, env, &next);
	while (*lst)
	{
		code = execute(*lst, env, next);
		if (code > 1 || code == -5)
			add_pid_back(pids, code);
		else if (code < 0 || code == 1)
		{
			free(pids);
			if ((*lst)->mode)
				return ((*lst)->mode);
			return (1);
		}
		go_next(lst, env, &next);
	}
	wait_all(pids, env);
	return (0);
}
