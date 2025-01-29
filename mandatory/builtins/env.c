#include "../h_files/minishell.h"

int	aff_env(t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (node->content && node->content[0])
			printf("%s=%s\n", node->name, node->content);
		node = node->next;
	}
	return (1);
}
