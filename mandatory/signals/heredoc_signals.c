
#include "../h_files/minishell.h"

void	inthandler(int sig)
{
	printf("sig : %d\n", sig);
	// exit(130);
}
