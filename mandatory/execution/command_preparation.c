#include "../h_files/minishell.h"

int	assign_node(t_list **node, int infile, int outfile, t_env **env)
{
	if (!node || !(*node))
	{
		if (infile > 2)
			close(infile);
		if (outfile > 2)
			close(outfile);
		return (0);
	}
	(*node)->input = infile;
	(*node)->output = outfile;
	if (infile < 0 || outfile < 0)
	{
		close_node(*node);
		exit_code(1, env, 0, NULL);
		return (-1);
	}
	init_node(*node, env);
	return (1);
}

int	prepare_command(t_list **node, t_env **env, int *next)
{
	int		infile;
	int		outfile;
	t_list	*command;

	infile = *next;
	outfile = 1;
	command = NULL;
	*next = 0;
	if (!(*node) || !(*node)->command)
		return (0);
	while (*node)
	{
		if (((*node)->type == 2 || (*node)->type == 3 || (*node)->type == HEREDOC) && open_file(*node, &infile, &outfile, next))
			exit_code(1, env, 0, NULL);
		else if ((*node)->type == 1)
			command = *node;
		if ((*node)->type == 2 && !command)
			command = (*node)->prev;
		if ((*node)->type == 2)
			break ;
		*node = (*node)->next;
	}
	signal(SIGINT, SIG_IGN);
	*node = command;
	return (assign_node(node, infile, outfile, env));
}
