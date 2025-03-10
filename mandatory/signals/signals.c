#include "../h_files/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_c = 130;
}

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit\n", 2);
}
