#include "../h_files/minishell.h"

int	wait_all(int *pids)
{
	int	i;
	int	status;

	i = 0;
	// while (pids[i] != -1)
	// {
	// 	waitpid(pids[i], &status, 0);
	// 	i++;
	// }
	waitpid(pids[0], &status, 0);
	free(pids);
	return (status);
}
