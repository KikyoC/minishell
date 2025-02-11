
#include "../h_files/minishell.h"

char	choose_quote(char *line)
{
	if (line[0] == '\'' || line[0] == '"')
		return (reverse_quote(line[0]));
	return ('"');
}

void	fill_word_quote(t_iterate *iter, char *final, char *word, char **env)
{
	char	*tmp;

	(void)env;
	tmp = getenv(word);
	iter->i += ft_strlen(word) + 1;
	free(word);
	if (!tmp)
		return ;
	cpy_text_add_quote(tmp, final, iter);
}

void	fill_word(t_iterate *iter, char *final, char *word, char **env)
{
	char	*tmp;

	(void)env;
	tmp = getenv(word);
	iter->i += ft_strlen(word) + 1;
	free(word);
	if (!tmp)
		return ;
	cpy_text(tmp, final, iter);
}
