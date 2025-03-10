#include "../h_files/minishell.h"

int	(*get_builtin(t_list *lst))(t_list *lst, t_env **env)
{
	if (!lst->command)
		return (NULL);
	else if (ft_strncmp("export", lst->command, 7) == 0)
		return (export);
	else if (ft_strncmp("unset", lst->command, 6) == 0)
		return (unset);
	else if (ft_strncmp("env", lst->command, 4) == 0)
		return (aff_env);
	else if (ft_strncmp("cd", lst->command, 3) == 0)
		return (cd);
	else if (ft_strncmp("echo", lst->command, 5) == 0)
		return (echo);
	else if (ft_strncmp("pwd", lst->command, 4) == 0)
		return (pwd);
	else if (ft_strncmp("exit", lst->command, 5) == 0)
		return (exit_builtin);
	return (NULL);
}

int	exec_builtin(t_list *c, int (*exe)(t_list *l, t_env **e), int n, t_env **e)
{
	int	state;

	if (exe == NULL)
		return (-1);
	if (n > 2)
		close(n);
	state = exe(c, e);
	close_node(c);
	return (state);
}
