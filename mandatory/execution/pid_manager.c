#include "../h_files/minishell.h"

int	wait_all(int *pids)
{
	int	state;
	int	i;

	state = 0;
	i = 0;
	while (pids[i] && i < 10)
	{
		waitpid(pids[i], &state, 0);
		i++;
	}
	return (state);
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
