#include "../h_files/minishell.h"

int	parse_exit_code(unsigned long long *res, char *str)
{
	int			i;
	long long	tmp;

	i = 0;
	if (!str)
	{
		if (res)
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
	if (res)
		*res = tmp;
	return (1);
}

void	transform_code(unsigned long long *code)
{
	while (*code > 255)
		*code %= 256;
}

t_env	*get_new_node(char *content)
{
	t_env	*res;

	res = ft_calloc(1, sizeof(t_env));
	if (!res)
		return (NULL);
	res->name = ft_strdup("?");
	res->content = ft_strdup(content);
	if (!res->name || !res->content)
		return (destroy(res));
	return (res);
}

int	exit_builtin(t_list *cmd, t_env **env)
{
	unsigned long long		code;
	t_env					*node;

	code = 0;
	if (cmd->flags)
	{
		if (!parse_exit_code(&code, cmd->flags[0]))
		{
			node = get_new_node(cmd->flags[0]);
			if (!node)
				exit_code(12, env, 0, NULL);
			else
				add_back(env, node, 0);
			return (-2);
		}
		if (cmd->flags[1])
		{
			ft_putstr_fd("exit\nExit: Too many arguments\n", 2);
			exit_code(1, env, 0, NULL);
			return (1);
		}
	}
	transform_code(&code);
	exit_code(code, env, 0, NULL);
	return (-2);
}
