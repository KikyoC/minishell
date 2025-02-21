
#include "../h_files/minishell.h"

char	*expand(char *line, t_env *env)
{
	int		len;
	char	*new_line;

	len = replace_dollars(env, line, NULL);
	new_line = ft_calloc(len + 1, sizeof(char));
	if (!new_line)
		free(line);
	replace_dollars(env, line, new_line);
	free(line);
	return (new_line);
}

int	exit_code(int code, t_env **env, int sub, t_list *cmd)
{
	t_env	*node;

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
	error_handler(code, sub, cmd->command);
	return (0);
}

void	cmd_found_handle(int *cmd_found, t_list *node)
{
	if (node->type == COMMAND)
		cmd_found++;
	else if (node->type == PIPE)
		cmd_found = 0;
}

static int	check_commands(t_list *cmds, t_env **env)
{
	t_list	*node;
	int		cmd_found;

	node = cmds;
	cmd_found = 0;
	while (node)
	{
		if ((node->type == HERE || node->type == REDIRECT
				|| node->type == PIPE) && !get_next(node))
			return (exit_code(2, env, 2, node));
		else if ((node->type == REDIRECT || node->type == PIPE)
			&& (!get_next(node) || get_next(node)->type != FILE))
			return (exit_code(2, env, 1, node));
		else if (node->type == HERE && (!get_next(node)
				|| get_next(node)->type != HEREDOC))
			return (exit_code(2, env, 2, node));
		else if ((node->type == PIPE || node->type == HERE
				|| node->type == REDIRECT) && node->been_quoted)
			return (exit_code(2, env, 3, node));
		cmd_found_handle(&cmd_found, node);
		node = node->next;
	}
	return (1);
}

t_list	*get_commands(char *line, t_env *env)
{
	t_list	*cmds;

	cmds = NULL;
	if (parse_quote(line))
	{
		exit_code(2, &env, 4, NULL);
		return (NULL);
	}
	cmds = ft_split_skip_quotes(line, '\0');
	if (!cmds)
		return (NULL);
	get_correct_commands(cmds, env);
	make_heredoc(&cmds, env);
	if (check_commands(cmds, &env))
		return (cmds);
	ft_lstclear(&cmds, free);
	return (NULL);
}
