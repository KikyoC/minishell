
#include "../h_files/minishell.h"

void	clean_flags(char **flags)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	if (!flags)
		return ;
	while (flags[i])
	{
		len = cpy_without_quote(NULL, flags[i]);
		tmp = ft_calloc(len + 2, sizeof(char));
		cpy_without_quote(tmp, flags[i]);
		free(flags[i]);
		flags[i] = tmp;
		i++;
	}
}

void	give_types(t_list **curr, int code)
{
	if (!code)
	{
		if (!(*curr)->been_quoted)
		{
			(*curr)->type = REDIRECT;
			if ((*curr)->next)
				(*curr)->next->type = FILE;
		}
		else
			(*curr)->type = COMMAND;
	}
	else
	{
		if (!(*curr)->been_quoted)
		{
			(*curr)->type = HERE;
			if ((*curr)->next)
				(*curr)->next->type = HEREDOC;
		}
		else
			(*curr)->type = COMMAND;
	}
}

static int	check_redirect(char *command)
{
	if (ft_strnstr(">>", command, 2)
		|| ft_strnstr("<", command, 1)
		|| ft_strnstr(">", command, 1))
		return (1);
	return (0);
}

static void	pipe_handle_parsing(t_list *curr)
{
	if (ft_strnstr("|", curr->command, 1) && !curr->been_quoted)
		curr->type = PIPE;
	else if (ft_strnstr("|", curr->command, 1) && curr->been_quoted)
		curr->type = COMMAND;
}

t_list	*get_correct_commands(t_list *cmds, t_env *env)
{
	t_list	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->type != HEREDOC)
			curr->content = expand((char *)curr->content, env, &curr);
		if (curr->type != COMMAND)
			remove_quote(curr->content, curr);
		clean_flags(curr->flags);
		if (curr->type == -1)
			curr->type = COMMAND;
		if (curr->type == FILE && curr->flags[0])
			modify_flags(&curr);
		if (curr->type == HEREDOC && curr->flags[0])
			file_flags(&curr);
		if (check_redirect(curr->command))
			give_types(&curr, 0);
		else if (ft_strnstr("<<", curr->command, 2))
			give_types(&curr, 1);
		pipe_handle_parsing(curr);
		curr = curr->next;
	}
	return (cmds);
}
