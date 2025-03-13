/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:09:57 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/13 13:20:06 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

int	children(t_list *cmd, t_env **env, char **envp, int next)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, handle_sigquit);
	if (next > 2)
		close(next);
	if (get_builtin(cmd) != NULL)
	{
		ft_free_split(envp);
		if (cmd->input > 2)
			close(cmd->input);
		exec_builtin(cmd, get_builtin(cmd), next, env);
		return (0);
	}
	if (cmd->input > 2)
		dup2(cmd->input, 0);
	if (cmd->output > 2)
		dup2(cmd->output, 1);
	close_node(cmd);
	execve(cmd->command, cmd->flags, envp);
	ft_free_split(envp);
	perror("Execution error");
	return (0);
}

int	execute(t_list *cmd, char **envp, t_env **env, int next)
{
	pid_t	f;
	int		state;

	state = pre_execute(cmd, envp, env);
	if (state < 0 || cmd->type != 1)
		return (state);
	if (!cmd->command)
	{
		ft_putstr_fd("Minishell: Command not found\n", 2);
		close_node(cmd);
		ft_free_split(envp);
		return (-5);
	}
	f = fork();
	if (f < 0)
	{
		perror("Minishell");
		return (1);
	}
	if (f == 0)
		return (children(cmd, env, envp, next));
	close_node(cmd);
	ft_free_split(envp);
	return (f);
}

t_list	*assign_command(t_list *cmd, int infile, int outfile, t_env **env)
{
	if (cmd && cmd->type == 1)
		init_node(cmd, env);
	if (!cmd || cmd->type != 1)
	{
		if (infile > 2)
			close(infile);
		if (outfile > 2)
			close(outfile);
		return (cmd);
	}
	cmd->input = infile;
	cmd->output = outfile;
	return (cmd);
}

t_list	*prepare_command(t_list	*node, int *next, t_env **env)
{
	int		infile;
	int		outfile;
	t_list	*command;

	infile = *next;
	outfile = 1;
	command = NULL;
	*next = 0;
	if (!node || !node->command)
		return (NULL);
	while (node)
	{
		if (node->type == 2 || node->type == 3 || node->type == HEREDOC)
			open_file(node, &infile, &outfile, next);
		else if (node->type == 1)
			command = node;
		if (node->type == 2 && !command)
			command = node->prev;
		if (node->type == 2)
			break ;
		node = node->next;
	}
	signal(SIGINT, SIG_IGN);
	return (assign_command(command, infile, outfile, env));
}

int	run(t_list **lst, t_env **env, int **pids)
{
	t_list	*cmd;
	int		next;
	int		exec;

	next = 0;
	cmd = prepare_command(*lst, &next, env);
	*pids = get_pid_list(*lst);
	if (!pids)
		return (12);
	while (cmd)
	{
		exec = execute(cmd, get_envp(env), env, next);
		if (exec > 1 || exec == -5)
			add_pid_back(*pids, exec);
		else if (exec != -1 && exec != -3)
		{
			free(*pids);
			return (exec);
		}
		cmd = cmd->next;
		while (cmd && cmd->prev->type != 2)
			cmd = cmd->next;
		cmd = prepare_command(cmd, &next, env);
	}
	return (1);
}
