/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_preparation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:05:25 by togauthi          #+#    #+#             */
/*   Updated: 2025/03/14 17:08:17 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

int	assign_node(t_list **node, int infile, int outfile, t_env **env)
{
	(*node)->input = infile;
	(*node)->output = outfile;
	if (infile < 0 || outfile < 0)
	{
		close_node(*node);
		exit_code(1, env, 0, NULL);
		return (-1);
	}
	if ((*node)->type == 1)
		init_node(*node, env);
	return (1);
}

int	file_open_failure(t_list *node, int *infile, int *outfile, int *next)
{
	return ((node->type == PIPE || node->type == FILE || node->type == HEREDOC)
		&& open_file(node, infile, outfile, next));
}

int	prepare_command(t_list **node, t_env **env, int *next)
{
	int		infile;
	int		outfile;
	t_list	*command;

	infile = *next;
	outfile = 1;
	command = *node;
	*next = 0;
	if (!(*node) || !(*node)->command)
		return (0);
	while (*node)
	{
		if (file_open_failure(*node, &infile, &outfile, next))
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
