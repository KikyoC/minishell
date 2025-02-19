#include "../h_files/minishell.h"

int	aff_env(t_list *lst, t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (node->content && node->content[0])
		{
			ft_putstr_fd(node->name, lst->output);
			ft_putchar_fd('=', lst->output);
			ft_putstr_fd(node->content, lst->output);
			ft_putchar_fd('\n', lst->output);
		}
		node = node->next;
	}
	return (1);
}
