
#include "../h_files/minishell.h"

char	**get_flags(char *line)
{
	t_list	*lst;
	int		size;
	char	**flags;
	int		i;
	t_list	*curr;

	i = 0;
	lst = ft_split_skip_quotes(line);
	curr = lst;
	size = ft_lstsize(lst);
	flags = ft_calloc (size + 1, sizeof(char *));
	flags[size] = NULL;
	while (i < size)
	{
		flags[i] = curr->content;
		i++;
	}
	ft_lstclear(&lst, free);
	return (flags);
}

int	remove_quote(char *line, t_list *cmds)
{
	int		i;
	int		j;
	int		size;
	char	*command;
	t_duet	duet;

	duet.single_quote = 0;
	duet.double_quote = 0;
	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '"')
		duet.double_quote = 1;
	else if (line[i] == '\'')
		duet.single_quote = 1;
	i++;
	size = len_quotes(duet, line);
	if (size == -1)
	{
		perror("parsing error: unterminated quote");
		return (-1);
	}
	command = ft_calloc(size + 1, sizeof(char));
	while (line[i])
	{
		if (line[i] == '"')
			break ;
		else if (line[i] == '\'')
			break ;
		command[j++] = line[i++];
	}
	cmds->command = command;
	cmds->flags = get_flags(line + i);
	return (0);
}
