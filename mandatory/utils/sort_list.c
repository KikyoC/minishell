
#include "../h_files/minishell.h"

t_env	*switch_nodes(t_env *node1, t_env *node2)
{
	char	*name;
	char	*content;

	name = node1->name;
	content = node1->content;
	node1->name = node2->name;
	node1->content = node2->content;
	node2->name = name;
	node2->content = content;
	return (node2);
}

char	**get_envp(t_env **env);
t_env	*get_env(char **envp);

t_env	*sort_env(t_env **e)
{
	t_env	*env;
	t_env	*node;
	char	**envp;

	envp = get_envp(e);
	if (!envp)
		return (NULL);
	env = get_env(envp);
	ft_free_split(envp);
	if (!env)
		return (NULL);
	node = env;
	while (node->next)
	{
		node = node->next;
		while (node->prev && ft_strncmp(node->name, node->prev->name, 500) < 0)
			node = switch_nodes(node, node->prev);
	}
	return (env);
}
