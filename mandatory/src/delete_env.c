
#include "../h_files/minishell.h"

void	*destroy_node(t_env *node)
{
	if (!node)
		return (NULL);
	if (node->name)
		free(node->name);
	if (node->content)
		free(node->content);
	free(node);
	return (NULL);
}

void	*destroy(t_env *env)
{
	t_env	*node;
	t_env	*next;

	node = env;
	while (node)
	{
		next = node->next;
		destroy_node(node);
		node = next;
	}
	return (NULL);
}

