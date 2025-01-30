#include "../h_files/minishell.h"

char	*fd_to_char(int fd);

void	write_env(char *actual, t_env **env, int fd, int *old)
{
	int		i;
	t_env	*node;
	char	*env_name;

	i = 0;
	while (ft_isalnum(actual[i]))
		i++;
	env_name = ft_substr(actual, 0, i);
	if (!env_name)
		return ;
	node = *env;
	while (node)
	{
		if (ft_strncmp(env_name, node->name, 500) == 0)
			break ;
		node = node->next;
	}
	free(env_name);
	*old += i;
	if (!node)
		return ;
	write(fd, node->content, ft_strlen(node->content));
}
