
#include "../h_files/minishell.h"
#include <stdio.h>

char	*expand(char *line, t_env *env)
{
	int		len;
	char	*new_line;

	len = replace_dollars(env, line, NULL);
	new_line = ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		free(line);
	replace_dollars(env, line, new_line);
	return (new_line);
}

t_list	*get_commands(char *line, t_env *env)
{
	t_list	*cmds;

	cmds = NULL;
	if (parse_quote(line))
	{
		perror("Segfault : unfinished quote");
		return (NULL);
	}
	cmds = ft_split_skip_quotes(line, '\0');
	if (!cmds)
		return (NULL);
	get_correct_commands(cmds, env);
	return (cmds);
}
