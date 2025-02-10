#include "../h_files/minishell.h"
#include <stdio.h>

static int	set_fd(t_list *node, int *fd, int flags)
{
	if (*fd > 2)
		close(*fd);
	*fd = open(node->command, flags);
	if (*fd < 0)
	{
		*fd = 0;
		perror("Minishell: ");
		return (1);
	}
	return (0);
}

static int	set_pipe(int *outfile, int *next)
{
	int	p[2];

	if (*outfile > 2)
	{
		close(*outfile);
		*outfile = 0;
	}
	if (pipe(p) < 0)
	{
		perror("Minishell: ");
		return (1);
	}
	*outfile = p[1];
	*next = p[0];
	return (0);
}

int	open_file(t_list *node, int *infile, int *outfile, int *next)
{
	if (ft_strncmp("<", node->prev->command, 2) == 0)
		return (set_fd(node, infile, O_RDONLY));
	if (ft_strncmp(">", node->prev->command, 2) == 0)
		return (set_fd(node, outfile, O_WRONLY | O_CREAT | O_TRUNC));
	if (ft_strncmp("|", node->command, 2) == 0)
		return (set_pipe(outfile, next));
	return (1);
}
