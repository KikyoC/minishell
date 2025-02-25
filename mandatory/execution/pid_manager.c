#include "../h_files/minishell.h"
#include <stdlib.h>

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
	exit_code(WEXITSTATUS(state), env, 0, NULL);	
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
