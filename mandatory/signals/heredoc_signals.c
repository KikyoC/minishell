
#include "../h_files/minishell.h"
#include <unistd.h>

void	inthandler(int sig)
{
	
	(void)sig;
	close(0);
	printf("^C\n");
}
