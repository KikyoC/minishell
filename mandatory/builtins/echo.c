#include "../h_files/minishell.h"

static char	*parse(char *str, int *new_line)
{
	int	i;
	int	var;

	i = 4;
	var = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i + 1] == 'n')
		*new_line = 0;
	if (*new_line)
		return (&str[i]);
	i += 2;
	while (str[i] == ' ')
		i++;
	return (&str[i]);
}

void	write_echo(char *str)
{
	int	in_quote;
	int	in_word;
	int	i;

	in_quote = -1;
	in_word = 1;
	i = -1;
	while (str[++i])
	{
		if (in_quote == -1 && i > 1 && str[i] != ' ' && str[i - 1] == ' ')
			write(1, " ", 1);
		if (str[i] == '"')
			in_quote = -in_quote;
		else if (str[i] == ' ' && in_quote == -1)
			continue ;
		else if (str[i] == '\\' && str[i + 1] == '"')
			write(1, &str[++i], 1);
		else
			write(1, &str[i], 1);
	}
}

void	echo(char *str)
{
	char	*final;
	int		new_line;

	new_line = 1;
	final = parse(str, &new_line);
	write_echo(final);
	if (new_line)
		write(1, "\n", 1);
}
