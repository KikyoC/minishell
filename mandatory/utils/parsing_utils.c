#include "../h_files/minishell.h"

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

int	is_operator(char str, int op)
{
	if ((str == '|' || str == '<'|| str == '>') && !op)
		return (1);
	else if ((str == '|' && op) || ((str == '<' || str == '>') && op == 2))
		return (-1000);
	else
		return (0);
}

int	reset(int *before, int *sign)
{
	*before = 0;
	*sign = 0;
	return (1);
}
