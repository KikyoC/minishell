

#include "../h_files/minishell.h"

t_list	*get_correct_commands(t_list *cmds)
{
	t_list	*curr;
	
	curr = cmds;
	while (curr)
	{
		if (!remove_quote(curr->content, cmds))
		{
			ft_lstclear(&cmds, free);
			return (NULL);
		}
		curr = curr->next;
	}
	return (cmds);
}

