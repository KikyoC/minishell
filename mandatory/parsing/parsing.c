
#include "../h_files/minishell.h"

char	*expand(char *line, t_env *env)
{
	int		len;
	char	*new_line;

	len = replace_dollars(env, line, NULL);
	new_line = ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		free(line);
	replace_dollars(env, line, new_line);
	free(line);
	return (new_line);
}

static int	check_commands(t_list *cmds)
{
	t_list	*node;
	int		cmd_found;

	node = cmds;
	cmd_found = 0;
	while (node)
	{
		if (node->type == 5 && (!node->next || node->next->type != 3))
			return (0);
		else if (node->type == 3 && (!node->prev || node->prev->type != 5))
			return (0);	
		else if (node->type == 2 && (!cmd_found || !node->next))
			return (0);
		else if (node->type == 1 && cmd_found)
			return (0);
		else if (node->type == 1)
			cmd_found ++;
		else if(node->type == 2)
			cmd_found = 0;
		node = node->next;
	}
	return (1);
}

t_list	*get_commands(char *line, t_env *env)
{
	t_list	*cmds;

	cmds = NULL;
	if (parse_quote(line))
	{
		ft_putstr_fd("Segfault : unfinished quote", 2);
		return (NULL);
	}
	cmds = ft_split_skip_quotes(line, '\0');
	if (!cmds)
		return (NULL);
	get_correct_commands(cmds, env);
	if (check_commands(cmds))
		return (cmds);
	ft_putstr_fd("Invalid line\n", 2);
	ft_lstclear(&cmds, free);
	return (NULL);
}
