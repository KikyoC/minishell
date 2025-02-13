
#include "../h_files/minishell.h"

char	**ft_realloc(char **split, char *to_add)
{
	int		len;
	char	**new;

	len = 0;
	if (split)
		while (split[len])
			len++;
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (NULL);
	len = 0;
	if (split)
	{
		while (split[len])
		{
			new[len] = ft_strdup(split[len]);
			len++;
		}
	}
	new[len] = ft_strdup(to_add);
	if (split)
		ft_free_split(split);
	return (new);
}
