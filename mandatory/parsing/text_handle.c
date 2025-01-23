
#include "../h_files/minishell.h"

char	**get_flags(char *line, t_list *cmds)
{
	t_list	*lst;
	int		size;
	char	**flags;
	int		i;
	t_list	*curr;

	i = 0;
	while (line[i] == ' ')
		i++;
	lst = ft_split_skip_quotes(line + i, ' ');
	curr = lst;
	size = ft_lstsize(lst);
	flags = ft_calloc (size + 1, sizeof(char *));
	flags[size] = NULL;
	i = 0;
	while (curr)
	{
		flags[i] = ft_strdup((char *)curr->content);
		i++;
		curr = curr->next;
	}
	ft_lstclear(&lst, free);
	cmds->flags = flags;
	return (flags);
}

char	*cpy_without_quote(char *line)
{
	int		i;
	int		len;
	char	*cpy;

	len = ft_strlen(line);
	cpy = ft_calloc(len - 1, sizeof(char));
	if (!cpy)
		return (NULL);
	i = 1;
	while ((line[i] != '\'' && line[i] != '"') && line[i])
	{
		cpy[i - 1] = line[i];
		i++;
	}
	free(line);
	return (cpy);
}

char	*quote_remover(char quote, char *line, char *command, int *i)
{
	while (line[++(*i)] && line[*i] != quote)
		command = ft_charjoin(command, line[*i]);
	return (command);
}

void	remove_quote(char *line, t_list *cmds)
{
	int		i;
	char	*command;

	i = -1;
	command = NULL;
	skip_spaces(line, &i);
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			command = quote_remover('\'', line, command, &i);
			cmds->been_quoted = 1;
		}
		else if (line[i] == '"')
		{
			command = quote_remover('"', line, command, &i);
			cmds->been_quoted = 1;
		}
		else if (line[i] == ' ')
			break ;
		else
			command = ft_charjoin(command, line[i]);
	}
	cmds->command = command;
	get_flags(line + i, cmds);
}
