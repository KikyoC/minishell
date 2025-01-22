
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

int	remove_quote(char *line, t_list *cmds)
{
	int		i;
	t_duet	duet;
	char	*command;

	duet.double_quote = 0;
	duet.single_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			command = quote_remover('\'', line, command, &i);
		else if (line[i] == '"')
			command = quote_remover('"', line, command, &i);
		else if (line[i] == ' ')
				break ;
		else


	}
}

int	get_infos(char *line, t_list *cmds)
{
	int	i;
	int	size;

	i = 0;
	while (line[i] == ' ' || line[i] == '\'' || line[i] == '"')
		i++;
	// while ()
	// size = len_quotes(duet, line + i);
	// if (size == -1 || !size)
	// 	return (-1);
	// command = ft_calloc(size + 1, sizeof(char));
	// if (!command)
	// 	return (-1);
	// while (line[i])
	// {
	// 	if (line[i] == '"')
	// 		break ;
	// 	else if (line[i] == '\'')
	// 		break ;
	// 	command[j++] = line[i++];
	// }
	// cmds->command = command;
	// get_flags(line + i + 1, cmds);
	return (0);
	//
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
