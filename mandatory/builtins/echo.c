#include "../h_files/minishell.h"
#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>

static char	*parse(char *str, int *new_line)
{
	int	i;

	i = 4;
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

int	try_print_home(char *str)
{
	char	*home;
	int		i;

	if (str[0] == '~' && (str[1] == '\0' || str[1] == ' '))
	{
		home = getenv("HOME");
		i = -1;
		if (home)	
			while (home[++i])
				write (1, &home[i], 1);
		return (1);
	}
	return (0);
}

void	write_echo(char *str)
{
	char	in_quote;
	int		i;

	in_quote = 0;
	i = -1;
	while (str[++i])
	{
		if (try_print_home(&str[i]))
			continue ;
		if (!in_quote && i > 1 && str[i] != ' ' && str[i - 1] == ' ')
			write(1, " ", 1);
		if (!in_quote && (str[i] == '"' || str[i] == '\''))
			in_quote = str[i];
		else if (in_quote && (str[i] == '"' || str[i] == '\''))
			in_quote = 0;
		else if (str[i] == ' ' && !in_quote)
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
