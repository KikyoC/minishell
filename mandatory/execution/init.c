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

int	is_file(char *str)
{
	struct stat	path_stat;

	if (!str)
		return (0);
	return (!stat(str, &path_stat) && !S_ISDIR(path_stat.st_mode));
}

int	good_command(t_list *lst, char **path)
{
	char	*tmp;
	int		i;
	char	*join;

	if (!access(lst->command, X_OK) && (!path || ft_strchr(lst->command, '/')))
		return (1);
	tmp = ft_strjoin("/", lst->command);
	if (!tmp)
		return (0);
	i = -1;
	while (path[++i])
	{
		join = ft_strjoin(path[i], tmp);
		if (is_file(join))
		{
			free(tmp);
			free(lst->command);
			lst->command = join;
			return (1);
		}
		if (join)
			free(join);
	}
	free(tmp);
	return (0);
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
		if (!good_command(lst, path))
		{
			free(lst->command);
			lst->command = NULL;
		}
	}
	if (path)
		ft_free_split(path);
}
