

#include "../h_files/minishell.h"

void	clean_flags(char **flags)
{
	int		i;

	i = 0;
	if (!flags)
		return ;
	while (flags[i])
	{
		if (flags[i][0] == '\'' || flags[i][0] == '"')
			flags[i] = cpy_without_quote(flags[i]);
		i++;
	}
}

t_list	*get_correct_commands(t_list *cmds)
{
	t_list	*curr;

	curr = cmds;
	while (curr)
	{
		if (remove_quote(curr->content, cmds) == -1)
		{
			ft_lstclear(&cmds, free);
			return (NULL);
		}
		// else
		// {
		// 	get_infos(curr->content, cmds);
		// }
		clean_flags(curr->flags);
		curr = curr->next;
	}
	return (cmds);
}

