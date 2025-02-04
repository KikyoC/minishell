
#include "../h_files/minishell.h"

t_list	*get_commands(char *line, char **env)
{
	t_list	*cmds;
	int		len;
	char	*new_line;

	if (parse_quotes(line))
	{
		perror("Segfault : unfinished quote");
		return (NULL);
	}
	len = replace_dollars(env, line, NULL); 
	new_line = ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		free(line);
	replace_dollars(env, line, new_line);
	cmds = ft_split_skip_quotes(new_line, '\0');
	free(new_line);
	get_correct_commands(cmds);
	return (cmds);
}
