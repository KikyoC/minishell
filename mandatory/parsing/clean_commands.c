
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
		if (curr->type != 1)
			remove_quote(curr->content, curr);
		if (!ft_strnstr(curr->command, "echo", 4))
			clean_flags(curr->flags);
		if (curr->type == -1)
			curr->type = 1;
		if (curr->type == 3 && curr->flags)
			modify_flags(&curr);
		if (ft_strnstr(">>", curr->command, 2) || ft_strnstr("<<", curr->command, 2)
				|| ft_strnstr("<", curr->command, 1) || ft_strnstr(">", curr->command, 1))
		{
			curr->type = 2;
			if (curr->next)
				curr->next->type = 3;
		}
		curr = curr->next;
	}
	return (cmds);
}
