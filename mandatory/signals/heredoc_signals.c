/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:05:29 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:05:33 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

void	inthandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		close(0);
		g_signal_c = 130;
	}
	else if (sig == SIGQUIT)
		return ;
}
