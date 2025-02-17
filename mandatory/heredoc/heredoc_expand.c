
#include "../h_files/minishell.h"

int	expand_here(char *flag, char *ptr, t_env *env)
{
	t_iterate	iter;
	char		*word;

	iter.i = 0;
	iter.j = 0;
	while (flag[iter.i])
	{
		word = check_dollars(flag, &iter);
		if (word)
			fill_word(&iter, ptr, flag, env);
		else
		{
			if (ptr)
				ptr[iter.j] = flag[(iter.i)];
			(iter.j)++;
			(iter.i)++;
		}
	}
	return (iter.j);
}

void	heredoc_expand(char **flags, t_env *env)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	tmp = NULL;
	if (!flags)
		return ;
	while (flags[i])
	{
		len = expand_here(flags[i], NULL, env);
		expand_here(flags[i], tmp, env);
		free(flags[i]);
		flags[i] = tmp;
		i++;
	}
}
