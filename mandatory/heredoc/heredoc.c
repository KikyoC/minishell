/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:08:51 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/12 16:35:39 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

void	make_heredoc(t_list **cmds, t_env *env)
{
	t_list	*curr;

	curr = *cmds;
	while (curr)
	{
		if (curr->type == HEREDOC && g_signal_c != 130)
		{
			if (curr->flags)
				ft_free_split(curr->flags);
			if (curr->command)
				curr->flags = heredoc(curr->command, ft_strlen(curr->command));
			else
				curr->flags = NULL;
			if (curr->flags && curr->been_quoted == 0)
				heredoc_expand(curr->flags, env);
		}
		curr = curr->next;
	}
}

void	handle_eof(char *line, char *final, int fd)
{
	if (line)
		free(line);
	else if (g_signal_c != 130 && !line)
	{
		ft_putstr_fd("Minishell: warning: NULL used as ", 2);
		ft_putstr_fd("end-of-file (wanted `", 2);
		ft_putstr_fd(final, 2);
		ft_putstr_fd("')\n", 2);
		free(line);
	}
	dup2(fd, 0);
}

char	**heredoc(char *final, int len)
{
	int		fd;
	char	*line;
	char	**tab;

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
	handle_eof(line, final, fd);
	close(fd);
	return (tab);
}
