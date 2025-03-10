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

int	is_good_skip_line(char *str)
{
	int	i;

	if (!str || !str[0] || !str[1] || str[0] != '-')
		return (1);
	i = 1;
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	echo(t_list *lst, t_env **env)
{
	int	new_line;

	new_line = 1;
	(void)env;
	if (!lst->flags || !lst->flags[0])
	{
		ft_putchar_fd('\n', lst->output);
		return (0);
	}
	new_line = is_good_skip_line(lst->flags[0]);
	if (new_line)
	{
		write_echo(lst->flags, lst);
		ft_putchar_fd('\n', lst->output);
	}
	else
		write_echo(&lst->flags[1], lst);
	return (0);
}
