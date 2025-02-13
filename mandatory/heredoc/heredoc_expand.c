
#include "../h_files/minishell.h"


int	expand_here(char *flag, char *ptr)
{}

char	*heredoc_expand(char **flags)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	while (flags[i])
	{
		len = expand_here(flags[i], NULL);
		tmp = ft_calloc(len + 1, sizeof(char));
		expand_here(flags[i], tmp);
	}

}
