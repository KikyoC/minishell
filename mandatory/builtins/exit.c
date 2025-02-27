#include "../h_files/minishell.h"

static int parse(unsigned long long *res, char *str)
{
	int			i;
	long long	tmp;

	i = 0;
	if (!str)
	{
		*res = 2;
		return (1);
	}
	if (!ft_isdigit(str[0]) && str[0] != '+' && str[0] != '-')
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	tmp = ft_atoi(str);
	if ((tmp == -1) && str[1])
		return (0);
	*res = tmp;
	return (1);
}

void	transform_code(unsigned long long *code)
{
	while (*code > 255)
		*code %= 256;
}

int	exit_builtin(t_list *cmd, t_env **env)
{
	unsigned long long		code;

	code = 0;
	if (cmd->flags)
	{
		if (cmd->flags[1])
		{
			ft_putstr_fd("Exit: Too many arguments\n", 2);
			exit_code(1, env, 0, NULL);
			return (1);
		}
		if (!parse(&code, cmd->flags[0]))
		{
			ft_putstr_fd("Exit: not valid number\n", 2);
			exit_code(2, env, 0, NULL);
			return (-2);
		}
	}
	transform_code(&code);
	exit_code(code, env, 0, NULL);
	return (-2);
}
