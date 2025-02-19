
#include "../h_files/minishell.h"

void	make_heredoc(t_list **cmds, t_env *env)
{
	t_list	*curr;

	curr = *cmds;
	while (curr)
	{
		if (curr->type ==  HEREDOC)
		{
			if (curr->flags)
				ft_free_split(curr->flags);
			curr->flags = heredoc(curr->command);
			if (curr->flags && curr->been_quoted == 0)
				heredoc_expand(curr->flags, env);
		}
		curr = curr->next;
	}
}

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
	while (!ft_strnstr(final, line, len))
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline(">");
		if (!line || ft_strnstr(final, line, len))
			break ;
		tab = ft_realloc(tab, line);
	}
	free(line);
	dup2(fd, 0);
	return (tab);
}
