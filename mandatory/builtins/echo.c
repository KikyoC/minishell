#include "../h_files/minishell.h"

void	write_echo(char **args, t_list *cmd)
{
	int		i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], cmd->output);
		i++;
		if (args[i])
			ft_putchar_fd(' ', cmd->output);
	}
}

int	echo(t_list *lst, t_env **env)
{
	int	new_line;

	new_line = 1;
	(void)env;
	if (ft_strncmp(lst->flags[0], "-n", 2) == 0)
		new_line = 0;
	if (new_line)
	{
		write_echo(lst->flags, lst);
		ft_putchar_fd('\n', lst->output);
	}
	else
		write_echo(&lst->flags[1], lst);
	return (0);
}
