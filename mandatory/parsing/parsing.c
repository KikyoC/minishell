
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

t_list	*get_commands(char *line, t_env *env)
{
	t_list	*cmds;
	t_list	*curr;

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
	curr = cmds;
	while (curr)
	{
		if (curr->type == 6)
			curr->flags = heredoc(curr->command);

		curr = curr->next;
	}
	return (cmds);
}
