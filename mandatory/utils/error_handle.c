
#include "../h_files/minishell.h"

void	print_error_parsing(int sub, char *command)
{
	if (sub == 1)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (sub == 2)
		ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n", 2);
}

void	error_handler(int code, int sub, char *command)
{
	if (code == 2)
		print_error_parsing(sub, command);
	else 
		printf("not handled for the moment ;(");
}
