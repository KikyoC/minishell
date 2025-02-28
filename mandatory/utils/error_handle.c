
#include "../h_files/minishell.h"

void	print_error_parsing(int sub, char *command)
{
	ft_putstr_fd("Minishell: ", 2);
	if (sub == 1)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (sub == 2)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
}

void	print_error_ambigous(void)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd("ambigous redirect\n", 2);
}

void	error_handler(int code, int sub, char *command)
{
	if (code == 2)
		print_error_parsing(sub, command);
	else if (code == 1)
		print_error_ambigous();
}

t_list	*get_next(t_list *cmds)
{
	t_list	*curr;

	curr = cmds->next;
	while (curr)
	{
		if (curr->command)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
