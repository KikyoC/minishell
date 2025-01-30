
#include "../h_files/minishell.h"

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
