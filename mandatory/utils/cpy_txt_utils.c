
#include "../h_files/minishell.h"

char	add_quotes(char quote, t_iterate *iter, char *final)
{
	if (final)
		final[iter->j] = reverse_quote(quote);
	(iter->j)++;
	if (final)
		final[iter->j] = quote;
	(iter->j)++;
	if (final)
		final[iter->j] = reverse_quote(quote);
	(iter->j)++;
	if (quote != '\0')
		return ('\0');
	return (quote);
}

void	cpy_text_add_quote(char *to_cpy, char *final, t_iterate *iter)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (to_cpy[i])
	{
		if ((to_cpy[i] == '\'' || to_cpy[i] == '"') && quote == '\0')
		{
			quote = add_quotes(to_cpy[i], iter, final);
			i++;
		}
		else if (to_cpy[i] == quote && to_cpy[i])
		{
			i++;
			quote = add_quotes(quote, iter, final);
		}
		else
		{
			if (final)
				final[iter->j] = to_cpy[i];
			(iter->j)++;
			i++;
		}
	}
}

void	cpy_text(char *to_cpy, char *final, t_iterate *iter)
{
	int	i;

	i = 0;
	while (to_cpy[i])
	{
		if (final)
			final[iter->j] = to_cpy[i];
		iter->j++;
		i++;
	}
}
