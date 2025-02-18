#include "../h_files/minishell.h"

static int	parse_end(int code, char *code_origin)
{
	char	*str;
	int		res;

	str = ft_itoa(code);
	if (!str)
		return (0);
	res = ft_strncmp(str, code_origin, ft_strlen(code_origin)) == 0;
	free(str);
	return (1);
}

int	exit_builtin(t_list *cmd, t_env **env)
{
	int		code;
	t_env	*node;

	code = 0;
	if (cmd->flags && cmd->flags[0])
	{
		code = ft_atoi(cmd->flags[0]);
		if (!parse_end(code, cmd->flags[0]))
			code = 2;
	}
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (-2);
	node->name = ft_strdup("?");
	node->content = ft_itoa(code);
	if (!node->name || !node->content)
	{
		destroy_node(node);
		return (-2);
	}
	add_back(env, node, 0);
	return (-2);
}
