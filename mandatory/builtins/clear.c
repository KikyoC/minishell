/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:19:54 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/10 17:55:55 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

void	clear(char **path)
{
	int		pid;
	char	*cmd;
	char	**c = ft_calloc(3, sizeof(char *));

	cmd = does_exist("clear", path);
	printf("%s\n",cmd);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, c, path);
	}
	waitpid(pid, NULL, 0);
}
