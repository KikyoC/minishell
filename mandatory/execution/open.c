#include "../h_files/minishell.h"

static int	set_fd(t_list *node, int *fd, int flags, int perms)
{
	if (*fd > 2)
		close(*fd);
	*fd = open(node->command, flags, perms);
	if (*fd < 0)
	{
		*fd = -1;
		perror("Minishell");
	}
	return (0);
}

static int	set_pipe(int *outfile, int *next)
{
	int	p[2];

	if (pipe(p) < 0)
	{
		perror("Minishell");
		return (1);
	}
	if (*outfile <= 2)
		*outfile = p[1];
	else
		close(p[1]);
	*next = p[0];
	return (0);
}

int	set_heredoc(t_list *cmd, int *infile)
{
	int	p[2];
	int	i;

	if (*infile > 2)
		close(*infile);
	if (pipe(p))
		return (1);
	i = -1;
	while (cmd->flags && cmd->flags[++i])
	{
		ft_putstr_fd(cmd->flags[i], p[1]);
		ft_putchar_fd('\n', p[1]);
	}
	close(p[1]);
	*infile = p[0];
	return (0);
}

int	open_file(t_list *node, int *infile, int *outfile, int *next)
{
	if (node->prev && ft_strncmp("<", node->prev->command, 2) == 0
		&& *infile >= 0 && *outfile >= 0)
		return (set_fd(node, infile, O_RDONLY, 0000));
	if (node->prev && ft_strncmp(">", node->prev->command, 2) == 0
		&& *infile >= 0 && *outfile >= 0)
		return (set_fd(node, outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (ft_strncmp("|", node->command, 2) == 0)
		return (set_pipe(outfile, next));
	if (node->prev && ft_strncmp(">>", node->prev->command, 3) == 0
		&& *infile >= 0 && *outfile >= 0)
		return (set_fd(node, outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (ft_strncmp("<<", node->prev->command, 3) == 0
		&& *infile >= 0 && *outfile >= 0)
		return (set_heredoc(node, infile));
	return (1);
}

int	is_pipe(t_list *cmd)
{
	if (!cmd)
		return (0);
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		if (cmd->type == 2)
		{
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
