
#include "../h_files/minishell.h"

char	**heredoc(char *final)
{
	int		len;
	char	*line;
	char	**tab;
	
	len = ft_strlen(final);
	line = NULL;
	tab = NULL;
	signal(SIGINT, inthandler);
	while (!ft_strnstr(final, line, len))
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline(">");
		tab = ft_realloc(tab, line);
	}
	return (tab);
}
