
#include "../h_files/minishell.h"

t_list	*get_commands(char *line)
{
	t_list	*cmds;

	cmds = ft_split_skip_quotes(line);
	get_correct_commands(cmds);
	return (cmds);
}
