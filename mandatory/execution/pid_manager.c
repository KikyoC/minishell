#include "../h_files/minishell.h"
#include <stdlib.h>
#include <sys/wait.h>

int	wait_all(int *pids, char *line, t_env **env)
{
	int	state;
	int	i;

	state = 0;
	i = 0;
	add_history(line);
	free(line);
	while (pids[i] && i < 10)
	{
		waitpid(pids[i], &state, 0);
		i++;
	}
	free(pids);
	if (WIFEXITED(state))
		exit_code(WEXITSTATUS(state), env, 0, NULL);
	else if (WIFSIGNALED(state))
	{
		if (WCOREDUMP(state))
			exit_code(WTERMSIG(state), env, 0, NULL);
		else
			exit_code(128 + WTERMSIG(state), env, 0, NULL);
	}
	
	signal(SIGINT, handle_sigint);
	return (WEXITSTATUS(state));
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
