
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
	if (!flags)
		return (NULL);
	i = 0;
	while (curr)
	{
		if (((char *)curr->content)[0] != ' ')
			flags[i++] = ft_strdup((char *)curr->content);
		curr = curr->next;
	}
	ft_lstclear(&lst, free);
	cmds->flags = flags;
	return (flags);
}

int cpy_without_quote(char *final, char *line)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	quote = '\0';
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && quote == '\0')
			quote = line[i];
		else if (line[i] == quote)
			quote = '\0';
		else
		{
			if (final)
				final[len] = line[i];
			len++;
		}
		i++;
	}
	return (len);
}

char	*quote_remover(char quote, char *line, char *command, int *i)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		command = ft_charjoin(command, line[*i]);
		(*i)++;
	}
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
		if (line[i] == '\'' || line[i] == '"')
		{
			command = quote_remover(line[i], line, command, &i);
			cmds->been_quoted = 1;
		}
		else if (line[i] == ' ')
			break ;
		else
			command = ft_charjoin(command, line[i]);
	}
	cmds->command = command;
	cmds->flags = get_flags(line + i, cmds);
	// if (cmds->type == 3)
		//pass
}
