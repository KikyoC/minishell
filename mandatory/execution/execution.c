#include "../h_files/minishell.h"
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
		execve(cmd->command, cmd->flags, env);
		perror("Execution error\n");
	}
	//Parent process
	ft_free_split(env);
	return (f);
}

static void	add_back(int *lst, int to_add)
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	while (lst[i] == -1)
		i++;
	lst[i] = to_add;
}

int	run(t_list **lst, t_env **env)
{
	t_list	*node;
	int		*pids;

	init(lst, env);
	node = *lst;
	pids = get_pid_list(*lst);
	while (node)
	{
		if (get_builtin(node) == NULL)
		{
			//Execute a normal command
			add_back(pids, execute(node, get_envp(env)));
		}
		else if (node->type == 1)
		{
			//Execute a builtin command
			add_back(pids, builtin(node, env, get_builtin(node)));
		}
		node = node->next;
	}
	return (wait_all(pids));
}
