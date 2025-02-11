#include "../h_files/minishell.h"

char	**get_envp(t_env **env);
char	*find_env(char *name, t_env **env);
void	init(t_list **lst, t_env **env);
int	(*get_builtin(t_list *lst))(t_list *lst, t_env **env);
int	*get_pid_list(t_list *lst);
int	wait_all(int *pids);
int	open_file(t_list *node, int *infile, int *outfile, int *next);
void	close_node(t_list *lst);
void	add_pid_back(int *fds, int fd);

void	children(t_list *cmd, char **envp, int next)
{
	printf("Infile is %i, outfile is %i, second flag is %s\n", cmd->input, cmd->output, cmd->flags[1]);
	if (cmd->input > 2)
		dup2(cmd->input, 0);
	if (cmd->output > 2)
		dup2(cmd->output, 1);
	if (next > 2)
		close(next);
	close_node(cmd);
	execve(cmd->command, cmd->flags, envp);
	perror("Execution error\n");
	exit(1);
}

int	execute(t_list *cmd, char **env, int next)
{
	pid_t	f;

	f = fork();
	if (f < 0)
	{
		perror("Minishell: ");
		return (1);
	}
	if (f == 0)
		children(cmd, env, next);
	close_node(cmd);
	ft_free_split(env);
	return (f);
}

t_list	*prepare_command(t_list	*node, int *next)
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
	if (!command)
		return (NULL);
	command->input = infile;
	command->output = outfile;
	return (command);
}

int	*run(t_list **lst, t_env **env)
{
	t_list	*command;
	char	**envp;
	int		next;
	int		*pids;

	next = 0;
	command = prepare_command(*lst, &next);
	pids = get_pid_list(*lst);
	if (!pids)
		return (NULL);
	while (command)
	{
		envp = get_envp(env);
		add_pid_back(pids, execute(command, envp, next));
		command = command->next;
		while (command && command->prev->type != 2)
			command = command->next;
		command = prepare_command(command, &next);
	}
	return (pids);
}
