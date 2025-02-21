#include "../h_files/minishell.h"

void	children(t_list *cmd, t_env **env, char **envp, int next)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (next > 2)
		close(next);
	if (get_builtin(cmd) != NULL)
	{
		ft_free_split(envp);
		if (cmd->input > 2)
			close(cmd->input);
		exec_builtin(cmd, get_builtin(cmd), next, env);
		return ;
	}
	if (cmd->input > 2)
		dup2(cmd->input, 0);
	if (cmd->output > 2)
		dup2(cmd->output, 1);
	close_node(cmd);
	execve(cmd->command, cmd->flags, envp);
	ft_free_split(envp);
	perror("Execution error");
}

void	signal_children()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);	
}

void	signal_parent()
{
	signal(SIGINT, SIG_IGN);
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
		return ((-1) - (ft_strncmp(cmd->command, "exit", 5) == 0));
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
	if (!node || !node->command)
		return (NULL);
	while (node)
	{
		if (node->type == 2 || node->type == 3 || node->type == HEREDOC)
			open_file(node, &infile, &outfile, next);
		else if (node->type == 1)
			command = node;
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
		if ((exec > 1 || exec == -1))
			add_pid_back(*pids, exec);
		else
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
