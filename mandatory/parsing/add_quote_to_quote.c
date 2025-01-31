
#include "../h_files/minishell.h"

static char	reverse_quote(char quote)
{
	if (quote == '\'')
		return ('"');
	else
		return ('\'');
}

void	put_quote(t_iterate *iter, char *new_line, char *line)
{
	if (new_line)
		new_line[iter->i + iter->j] = reverse_quote(line[iter->i]);
	iter->j++;
	if (new_line)
		new_line[iter->i + iter->j] = line[iter->i];
	iter->j++;
	if (new_line)
		new_line[iter->i + iter->j] = reverse_quote(line[iter->i]);
}

int	add_quote_to_quote(char *line, char *new_line)
{
	t_iterate	iter;
	char		quote;

	iter.i = 0;
	iter.j = 0;
	while (line[iter.i])
	{
		if (line[iter.i] == '\'' || line[iter.i] == '"')
		{
			quote = line[iter.i];
			put_quote(&iter, new_line, line);
		}
		else
		{
			if (new_line)
				new_line[iter.i + iter.j] = line[iter.i];
		}
		iter.i++;
	}
	return (iter.j + iter.i);
}
