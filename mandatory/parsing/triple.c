
#include "../h_files/minishell.h"

int triple(t_list *cmds, t_env **env)
{
	t_list	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->type == 1 && curr->command && curr->command[0] == '|')
			return (exit_code(2, env, 2, curr));
		else if (curr->type == 1 && curr->command && curr->command[0] == '<')
			return (exit_code(2, env, 2, curr));
		else if (curr->type == 1 && curr->command && curr->command[0] == '>')
			return (exit_code(2, env, 2, curr));
		curr = curr->next;
	}
	return (1);
}
