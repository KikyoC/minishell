
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
