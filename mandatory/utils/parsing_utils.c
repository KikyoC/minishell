
#include "../h_files/minishell.h"

int	is_operator(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (1);
	return (0);
}

t_list	*find_operator(int *i, char *line)
{
	t_list	*node;
	char	*str;
	int		count;

	count = 0;
	while (!is_operator(line[count]) && line[count])
		count++;
	str = ft_calloc(count + 1, sizeof(char));
	while (--count >= 0)
	{
		str[count] = line[count];
		(*i)++;
	}
	node = ft_lstnew(str);
	return (node);
}

int	skip_quotes(char *line, char ch, int *i)
{
	while (line[*i])
	{
		if (ch == '"' || ch == '\'')
			break ;
		(*i)++;
	}
	return (*i);
}

t_list	*ft_split_skip_quotes(char *line)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = NULL;
	while (line[i])
	{
		if (line[i] == '\'')
			skip_quotes(line, '\'', &i);
		else if (line[i] == '"')
			skip_quotes(line, '"', &i);
		else if (!is_operator(line[i]))
			ft_lstadd_back(&lst, find_operator(&i, line + i));
		else if (is_operator(line[i]))
			ft_lstadd_back(&lst, check_until(line + i, &i));
	}
	return (lst);
}

int	quote_parsing(char *command)
{
	int	quote;
	int	double_quote;
	int	i;

	i = -1;
	quote = 0;
	double_quote = 0;
	while (command[++i])
	{
		if (command[i] == '\'')
			quote++;
		else if (command[i] == '"')
			double_quote++;
	}
	return (!(quote % 2) && !(double_quote % 2));
}
