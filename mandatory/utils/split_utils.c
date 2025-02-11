
#include "../h_files/minishell.h"

int	split_len(char **spl)
{
	int	i;

	i = 0;
	while (spl[i])
		i++;
	return (i);
}

char	**split_realloc(char **old, char **cpy, int	*index)
{
	int	i;

	i = 0;
	while (old[i])
	{
		cpy[*index] = ft_strdup(old[i]);
		i++;
		(*index)++;
	}
	ft_free_split(old);
	return (cpy);
}
