
#include "../h_files/minishell.h"

int	is_operator(char ch, char c)
{
	if (ch == '>' || ch == '<' || ch == '|' || ch == c)
		return (1);
	return (0);
}

t_list	*find_operator(int *i, char *line, char ch)
{
	t_list	*node;
	char	*str;
	int		count;
	int		little;
	int		big;

	count = 0;
	little = 0;
	big = 0;
	while ((!is_operator(line[count], ch) || big % 2 != 0
			|| little % 2 != 0) && line[count])
	{
		if (line[count] == '\'' && big % 2 == 0)
			little++;
		else if (line[count] == '"' && little % 2 == 0)
			big++;
		count++;
	}
	str = ft_calloc(count + 1, sizeof(char));
	if (!str)
		return (NULL);
	(*i) += count;
	while (--count >= 0)
		str[count] = line[count];
	node = ft_lstnew(str);
	return (node);
}

t_list	*ft_split_skip_quotes(char *line, char ch)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = NULL;
	while (line[i])
	{
		if (!is_operator(line[i], ch))
			ft_lstadd_back(&lst, find_operator(&i, line + i, ch));
		else
			ft_lstadd_back(&lst, check_until(line + i, &i, ch));
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

int	len_quotes(t_duet duet, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && duet.single_quote != -1)
			return (i);
		else if (line[i] == '"' && duet.double_quote != -1)
			return (i);
		i++;
	}
	return (-1);
}
