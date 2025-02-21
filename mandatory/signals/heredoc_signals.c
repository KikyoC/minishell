
#include "../h_files/minishell.h"

void	inthandler(int sig)
{
	(void)sig;
	close(0);
	printf("^C\n");
}
