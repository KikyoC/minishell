#include "../h_files/minishell.h"

void	good_flags(t_list *lst)
{
	char	**res;
	int		i;

	i = 0;
	if (!lst->flags)
		return ;
	while (lst->flags[i])
		i++;
	res = ft_calloc(i + 2, sizeof(char *));
	res[0] = ft_strdup(lst->command);
	if (!res[0])
	{
		free(res);
		return ;
	}
	i = 0;
	while (lst->flags[++i - 1])
		res[i] = lst->flags[i - 1];
	free(lst->flags);
	lst->flags = res;
}

void	good_command(t_list *lst, char **path)
{
	char	*tmp;
	int		i;
	char	*join;

	if (access(lst->command, X_OK) == 0 && access(lst->command, F_OK) == 0)
		return ;
	tmp = ft_strjoin("/", lst->command);
	if (!tmp)
		return ;
	i = -1;
	while (path[++i])
	{
		join = ft_strjoin(path[i], tmp);
		if (access(join, X_OK) == 0)
		{
			free(tmp);
			free(lst->command);
			lst->command = join;
			return ;
		}
		free(join);
	}
	free(tmp);
}

void	init_node(t_list *lst, t_env **env)
{
	char	**path;

	path = NULL;
	if (find_env("PATH", env) != NULL)
		path = ft_split(find_env("PATH", env), ":");
	if (get_builtin(lst) == NULL && lst->type == 1)
	{
		good_flags(lst);
		if (path)
			good_command(lst, path);
	}
	if (path)
		ft_free_split(path);
}

int	*get_pid_list(t_list *lst)
{
	int	*res;
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	res = ft_calloc(i + 1, sizeof(int));
	if (!res)
		return (NULL);
	return (res);
}
