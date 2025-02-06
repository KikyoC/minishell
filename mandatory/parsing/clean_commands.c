
#include "../h_files/minishell.h"

void	clean_flags(char **flags)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	if (!flags)
		return ;
	while (flags[i])
	{
		len = cpy_without_quote(NULL, flags[i]);
		tmp = ft_calloc(len + 2, sizeof(char));
		cpy_without_quote(tmp, flags[i]);
		free(flags[i]);
		flags[i] = tmp;
		i++;
	}
}

t_list	*get_correct_commands(t_list *cmds, char **env)
{
	t_list	*curr;

	curr = cmds;
	while (curr)
	{
		curr->content = expand((char *)curr->content, env);
		if (curr->type != 1)
			remove_quote(curr->content, curr);
		clean_flags(curr->flags);
		if (curr->type == -1)
			curr->type = 1;
		if (curr->type == 3 && curr->flags[0])
			modify_flags(&curr);
		if (ft_strnstr(">>", curr->command, 2)
				|| ft_strnstr("<", curr->command, 1) || ft_strnstr(">", curr->command, 1))
		{
			curr->type = 5;
			if (curr->next)
				curr->next->type = 3;
		}
		if (ft_strnstr("<<", curr->command, 2))
		{
			curr->type = 4;
			if (curr->next)
				curr->next->type = 6;
		}
		if (ft_strnstr("|", curr->command, 1))
			curr->type = 2;
		curr = curr->next;
	}
	return (cmds);
}
