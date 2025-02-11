
#include "../h_files/minishell.h"

int parse_quote(char *line)
{
	char	quote;
	int	i;

	i = 0;
	quote = '\0';
	while (line[i])
	{
		if (line[i] == quote)
			quote = '\0';
		else if ((line[i] == '\'' || line[i] == '"') && !quote)
			quote = line[i];
		i++;
	}
	return (quote);
}
