
#include "../h_files/minishell.h"

int	handle_ambigous(t_env *env, t_list **cmds)
{
	t_list	*curr;
	char	*word;
	int		i;

	curr = *cmds;
	i = 0;
	while (curr)
	{
		if (curr->type == REDIRECT)
		{
			if (curr->next && curr->next->been_expanded)
			{
				word = (char *)curr->next->content;
				while (is_operator(word[i], ' '))
					i++;
				if (((char *)curr->next->content)[i] == '\0')
				{
					return (exit_code(1, &env, 1, curr->next));
				}
			}
		}
		curr = curr->next;
	}
	return (1);
}
