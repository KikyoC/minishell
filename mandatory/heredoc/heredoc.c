
#include "../h_files/minishell.h"

char	**heredoc(char *final)
{
	int		len;
	char	*line;
	char	**tab;
	int		fd;

	len = ft_strlen(final);
	line = NULL;
	tab = NULL;
	fd = dup(0);
	signal(SIGINT, inthandler);
	while (!ft_strncmp(final, line, len))
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline(">");
		if (!line)
			break ;
		tab = ft_realloc(tab, line);
	}
	free(line);
	dup2(fd, 0);
	return (tab);
}
