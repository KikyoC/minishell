
#include "../h_files/minishell.h"

void	inthandler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		printf("^C\n");
		g_signal_c = 130;
	}
	else if (sig == SIGQUIT)
		return ;
}
