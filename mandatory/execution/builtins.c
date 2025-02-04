#include "../h_files/minishell.h"

int	echo(t_list *lst, t_env **env);
int	cd(t_list *lst, t_env **env);
int	aff_env(t_list *lst, t_env **env);
int	export(t_list *lst, t_env **env);
int	unset(t_list *lst, t_env **env);
int	pwd(t_list *lst, t_env **env);

int	(*get_builtin(t_list *lst))(t_list *lst, t_env **env)
{
	if (ft_strncmp("export", lst->command, 7) == 0)
		return (export);
	else if (ft_strncmp("unset", lst->command, 6) == 0)
		return(unset);
	else if (ft_strncmp("env", lst->command, 4) == 0)
		return(aff_env);
	else if (ft_strncmp("cd", lst->command, 3) == 0)
		return(cd);
	else if (ft_strncmp("echo", lst->command, 5) == 0)
		return(echo);
	else if (ft_strncmp("pwd", lst->command, 4) == 0)
		return(pwd);
	return (NULL);
}

int	execute_builtin(t_list *lst, int from, int to, t_env **env)
{
	int		(*execute)(t_list *lst, t_env **env);
	pid_t	f;

	execute = get_builtin(lst);
	if (!execute)
		return (-2);
	f = fork();
	if (f == -1)
	{
		perror("Minishell: ");
		return (-1);
	}
	if (f == 0)
	{
		if (from > 0)
			dup2(from , 0);
		if (to > 0)
			dup2(to, 1);
		execute(lst, env);
		exit(0);
	}
	return (f);
}
