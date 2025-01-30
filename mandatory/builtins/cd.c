#include "../h_files/minishell.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

char	*parse_quotes(char *str, int multiple_args, t_env **env);

char	*find(char *str, t_env **env)
{
	t_env	*node;
	size_t	len;

	node = *env;
	len = ft_strlen(str);
	while (node)
	{
		if (ft_strncmp(str, node->name, len) == 0)
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

char	*get_home(t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strncmp("HOME", node->name, 4) == 0 && node->content[0])
		{
			return (node->content);	
		}
		node = node->next;
	}
	ft_putstr_fd("Minishell: HOME not set\n", 2);
	return (NULL);
}

int	cd(t_list *lst, t_env **env)
{
	char	*final;

	if (lst->flags == NULL || lst->flags[0] == NULL)
		final = get_home(env);
	else if (lst->flags[0] && lst->flags[1])
	{
		ft_putstr_fd("Minishell: Only 1 argument is supported with this function\n", 2);
		return (0);
	}
	else
		final = parse_quotes(lst->flags[0], 1, env);
	if (!final)
		return (1);
	if (chdir(final))
	{
		perror("Minishell: ");
		if (lst->flags && lst->flags[0])
			free(final);
		return (errno);
	}
	if (lst->flags && lst->flags[0])
		free(final);
	return (0);
}
