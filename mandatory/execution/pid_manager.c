#include "../h_files/minishell.h"

void	wait_all(int *pids, char *line, t_env **env)
{
	int	state;
	int	i;

	state = 0;
	i = 0;
	add_history(line);
	free(line);
	while (pids[i])
	{
		waitpid(pids[i], &state, 0);
		i++;
	}
	free(pids);
	if (i && WIFEXITED(state))
		exit_code(WEXITSTATUS(state), env, 0, NULL);
	else if (i && WIFSIGNALED(state))
	{
		if (WCOREDUMP(state))
			exit_code(WTERMSIG(state), env, 0, NULL);
		else
			exit_code(128 + WTERMSIG(state), env, 0, NULL);
	}
	signal(SIGINT, handle_sigint);
}

void	add_pid_back(int *pids, int pid)
{
	int	i;

	if (pid <= 0)
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
