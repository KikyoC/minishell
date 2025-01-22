#include "../h_files/minishell.h"

int	aff_env(t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		printf("%s=%s\n", node->name, node->content);
		node = node->next;
	}
	return (1);
}
