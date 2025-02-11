
#include "../h_files/minishell.h"
#include <stdio.h>

char	*expand(char *line, char **env)
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

t_list	*get_commands(char *line, char **env)
{
	t_list	*cmds;

	if (parse_quote(line))
	{
		perror("Segfault : unfinished quote");
		return (NULL);
	}
	cmds = ft_split_skip_quotes(line, '\0');
	get_correct_commands(cmds, env);
	return (cmds);
}
