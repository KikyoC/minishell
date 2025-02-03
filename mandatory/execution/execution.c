#include "../h_files/minishell.h"
#include <stdio.h>

char	**get_envp(t_env **env);
char	*find_env(char *name, t_env **env);

char	**create_args(char *cmd, char **flags)
{
	int		i;
	char	**res;

	i = 0;
	while (flags[i])
		i++;
	res = ft_calloc(i + 2, sizeof(char *));
	if (!res)
		return (flags);
	res[0] = ft_strdup(cmd);
	if (!res[0])
	{
		free(res);
		return (flags);
	}
	i = 1;
	while (flags[i - 1])
	{
		res[i] = flags[i - 1];
		i++;
	}
	free(flags);
	return (res);
}

char	*get_command(char **path, char *command)
{
	char	*tmp;
	int		i;
	char	*join;

	if (access(command, X_OK) == 0 && access(command, F_OK) == 0)
		return (ft_strdup(command));
	tmp = ft_strdup(command);
	if (!tmp)
		return (NULL);
	command = ft_strjoin("/", tmp);
	free(tmp);
	if (!command)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		join = ft_strjoin(path[i], command);
		if (access(join, X_OK) == 0)
		{
			free(command);
			return (join);
		}
		free(join);
	}
	free(command);
	return (NULL);
}

int	execute(t_list *cmd, int from, int to, char **env)
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
		if (from > 0)
			dup2(from , 0);
		if (to > 0)
			dup2(to, 1);
		execve(cmd->command, cmd->flags, env);
		perror("Execution error\n");
	}
	//Parent process
	return (f);
}

int	run(t_list **lst, t_env **env)
{
	t_list	*current;
	char	**envp;
	char	*command;
	char	**path;

	current = *lst;
	envp = get_envp(env);
	if (!envp)
	{
		perror("Minishell: ");
		return (1);
	}
	(*lst)->flags = create_args((*lst)->command, (*lst)->flags);
	path = ft_split(find_env("PATH", env), ":");
	command = get_command(path, (*lst)->command);
	if (path)
		ft_free_split(path);
	if (!command)
		return (127);
	free((*lst)->command);
	(*lst)->command = command;
	execute(*lst, -1, -1, envp);
	ft_free_split(envp);
	return (1);
}
