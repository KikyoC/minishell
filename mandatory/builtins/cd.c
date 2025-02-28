#include "../h_files/minishell.h"

static t_env	*find(char *str, t_env **env)
{
	t_env	*node;
	size_t	len;

	node = *env;
	len = ft_strlen(str);
	while (node)
	{
		if (ft_strncmp(str, node->name, len) == 0)
			return (node);
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
			return (node->content);
		node = node->next;
	}
	ft_putstr_fd("Minishell: HOME not set\n", 2);
	return (NULL);
}

void	switch_pwd(t_env **env)
{
	t_env	*old;
	t_env	*current;
	char	*current_path;

	current_path = getcwd(NULL, PATH_MAX);
	if (!current_path)
		return ;
	old = find("OLDPWD", env);
	current = find("PWD", env);
	if (!old || !current)
		return ;
	free(old->content);
	old->content = current->content;
	current->content = current_path;
}

int	cd(t_list *lst, t_env **env)
{
	char	*final;

	if (lst->flags == NULL || lst->flags[0] == NULL)
		final = get_home(env);
	else if (lst->flags[0] && lst->flags[1])
	{
		ft_putstr_fd(
			"Minishell: Only 1 argument is supported with this function\n", 2);
		return (0);
	}
	else
		final = lst->flags[0];
	if (!final)
		return (1);
	if (chdir(final))
	{
		perror("Minishell");
		return (errno);
	}
	switch_pwd(env);
	return (0);
}
