
#include "../h_files/minishell.h"

void	cpy_text(char *to_cpy, char *final)
{
	int	j;

	j = 0;
	while (to_cpy[j])
	{
		if (final)
			final[j] = to_cpy[j];
		j++;
	}
}

void	fill_word(t_iterate *iter, char *final, char *word, char **env)
{
	char	*tmp;

	(void)env;
	tmp = getenv(word);
	iter->i += ft_strlen(word);
	free(word);
	if (!tmp)
		return ;
	if (final)
		cpy_text(tmp, final);
	iter->j += ft_strlen(tmp);
}
