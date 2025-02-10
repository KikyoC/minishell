#include "../h_files/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char	**get_envp(t_env **env);
char	*find_env(char *name, t_env **env);
void	init(t_list **lst, t_env **env);
int	(*get_builtin(t_list *lst))(t_list *lst, t_env **env);
int	*get_pid_list(t_list *lst);
int	wait_all(int *pids);

int	builtin(t_list *cmd, t_env **env, int (execute)(t_list *lst, t_env **env))
{
	pid_t	f;

	f = fork();
	if (f < 0)
	{
		perror("Minishell: ");
		return (1);
	}
	if (f == 0)
	{
		//Child process
		execute(cmd, env);
		exit(0);
	}
	//Parent process
	return (f);
}

int	execute(t_list *cmd, char **env)
{
	pid_t	f;

	f = fork();
	if (f < 0)
	{
		perror("Minishell: ");
		return (1);
	}
	if (f == 0)
	{
		//Child process
		printf("Input is %i\n", cmd->input);
		dup2(cmd->input, 0);
		// close(cmd->input);
		execve(cmd->command, cmd->flags, env);
		perror("Execution error\n");
	}
	//Parent process
	ft_free_split(env);
	return (f);
}

// static void	add_back(int *lst, int to_add)
// {
// 	int	i;
//
// 	i = 0;
// 	if (!lst)
// 		return ;
// 	while (lst[i] == -1)
// 		i++;
// 	lst[i] = to_add;
// }

// Actually it can handle < and >
int	open_file(t_list *node, int *infile, int *outfile)
{
	if (ft_strncmp("<", node->prev->command, 2))
	{
		close(*infile);
		*infile = open(node->command, O_RDONLY);
		if (*infile < 0)
		{
			*infile = 0;
			perror("Minishell: ");
			return (1);
		}
		return (0);
	}
	if (ft_strncmp(">", node->prev->command, 2))
	{
		close(*outfile);
		*outfile = open (node->command, O_WRONLY | O_TRUNC | O_CREAT);
		if (*outfile < 0)
		{
			*outfile = 1;
			perror("Minishell: ");
			return (1);
		}
		return (0);
	}
	return (1);
}

t_list	*prepare_command(t_list	*node)
{
	int		infile;
	int		outfile;
	t_list	*command;

	infile = 0;
	outfile = 1;
	command = NULL;
	while (node)
	{
		// If it's a file
		if (node->type == 4)
		{
			printf("It's a file\n");
			open_file(node, &infile, &outfile);
		}
		else if (node->type == 1)
			command = node;
		node = node->next;
	}
	command->input = open("infile", O_RDONLY);
	printf("Input is %i\n", command->input);
	command->output = outfile;
	return (command);
}

int	run(t_list **lst, t_env **env)
{
	t_list	*command;
	char	**envp;
	int		state;

	command = prepare_command(*lst);
	envp = get_envp(env);
	(void)command;
	(void)envp;
	(void)state;
	// waitpid(execute(command, envp), &state, 0);
	return (1);
}
