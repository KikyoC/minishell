
#include "../h_files/minishell.h"

char	**ft_realloc(char **split, char *to_add)
{
	int		len;
	char	**new;

	len = 0;
	while (split[len])
		len++;
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (NULL);
	len = -1;
	while (split[++len])
		new[len] = ft_strdup(split[len]);
	new[len] = ft_strdup(to_add);
	return (new);
}
