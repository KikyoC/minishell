#include "../h_files/minishell.h"

void	children(t_list *cmd, t_env **env, char **envp, int next)
{
	if (get_builtin(cmd) != NULL)
	{
		ft_free_split(envp);
		exec_builtin(cmd, get_builtin(cmd), next, env);
		return ;
	}
	if (cmd->input > 2)
		dup2(cmd->input, 0);
	if (cmd->output > 2)
		dup2(cmd->output, 1);
	if (next > 2)
		close(next);
	close_node(cmd);
	execve(cmd->command, cmd->flags, envp);
	ft_free_split(envp);
	perror("Execution error");
}

int	execute(t_list *cmd, char **envp, t_env **env, int next)
{
	pid_t	f;

	if (get_builtin(cmd) != NULL && !is_pipe(cmd))
		exec_builtin(cmd, get_builtin(cmd), 0, env);
	if (cmd->input < 0 || cmd->output < 0
		|| (get_builtin(cmd) && !is_pipe(cmd)))
	{
		ft_free_split(envp);
		close_node(cmd);
		return (-1);
	}
	f = fork();
	if (f < 0)
	{
		perror("Minishell");
		return (1);
	}
	if (f == 0)
	{
		children(cmd, env, envp, next);
		return (0);
	}
	close_node(cmd);
	ft_free_split(envp);
	return (f);
}

t_list	*assign_command(t_list *cmd, int infile, int outfile, t_env **env)
{
	if (cmd)
		init_node(cmd, env);
	if (!cmd)
	{
		if (infile > 2)
			close(infile);
		if (outfile > 2)
			close(outfile);
		return (NULL);
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
	while (node)
	{
		if (node->type == 2 || node->type == 3)
			open_file(node, &infile, &outfile, next);
		else if (node->type == 1)
			command = node;
		if (node->type == 2)
			break ;
		node = node->next;
	}
	return (assign_command(command, infile, outfile, env));
}

int	run(t_list **lst, t_env **env, int **pids)
{
	t_list	*command;
	int		next;
	int		execution;

	next = 0;
	command = prepare_command(*lst, &next, env);
	*pids = get_pid_list(*lst);
	if (!pids)
		return (12);
	while (command)
	{
		execution = execute(command, get_envp(env), env, next);
		if (execution > 0 || execution == -1)
			add_pid_back(*pids, execution);
		else
		{
			free(*pids);
			return (execution);
		}
		command = command->next;
		while (command && command->prev->type != 2)
			command = command->next;
		command = prepare_command(command, &next, env);
	}
	return (1);
}
