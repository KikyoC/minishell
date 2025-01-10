/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:19:54 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/10 18:09:32 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

void	clear(char **path)
{
	int		pid;
	char	*c[2] = {NULL, NULL};

	pid = fork();
	if (pid == 0)
		execve("/usr/bin/clear", c, path);
	else
		waitpid(pid, NULL, 0);
}
