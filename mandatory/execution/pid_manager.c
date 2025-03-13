/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:09:42 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/13 17:34:56 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"
#include <stdlib.h>

int		set_special_code(int pid, t_env **env)
{
	if (pid == -5)
	{
		exit_code(127, env, 0, NULL);
		return (1);
	}
	return (0);
}

void	wait_all(int *pids, t_env **env)
{
	int	state;
	int	i;

	state = 0;
	i = -1;
	while (pids[++i])
		if (pids[i] > 0)
			waitpid(pids[i], &state, 0);
	if (i && set_special_code(pids[i - 1], env))
		i = 0 ;
	else if (i && WIFEXITED(state))
		exit_code(WEXITSTATUS(state), env, 0, NULL);
	else if (i && WIFSIGNALED(state))
	{
		if (WCOREDUMP(state))
			exit_code(WTERMSIG(state), env, 0, NULL);
		else
			exit_code(128 + WTERMSIG(state), env, 0, NULL);
	}
	free(pids);
	signal(SIGINT, handle_sigint);
}

void	add_pid_back(int *pids, int pid)
{
	int	i;

	if (pid <= 0 && pid != -5)
		return ;
	i = 0;
	while (pids[i])
		i++;
	pids[i] = pid;
}

int	*get_pid_list(t_list *lst)
{
	int	*res;
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	res = ft_calloc(i + 1, sizeof(int));
	if (!res)
		return (NULL);
	return (res);
}
