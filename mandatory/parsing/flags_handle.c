
#include "../h_files/minishell.h"

t_list	*find_command(t_list *cmd)
{
	t_list	*curr;

	curr = cmd;
	while (curr && curr->type != 1)
		curr = curr->prev;
	if (curr)
		return (curr);
	return (NULL);
}

char	**split_flags(char **flags)
{
	int		i;
	char	**cpy;

	i = 0;
	while (flags[i])
		i++;
	cpy = calloc(i - 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	cpy[i - 1] = NULL;
	i -= 2;
	while (i >= 0)
	{
		cpy[i] = strdup(flags[i]);
		i--;
	}
	(*flags) = NULL;
	return (cpy);
}

char	**give_flags(t_list *curr, t_list *cmds)
{
	int len;
	int	index;
	char	**new;

	index = 0;
	len = split_len(curr->flags) + split_len(cmds->flags);
	new = ft_calloc(len + 1, sizeof(char *));
	new[len] = NULL;
	split_realloc(curr->flags, new, &index);
	curr->flags = NULL;
	split_realloc(cmds->flags, new, &index);
	cmds->flags = NULL;
	return (new);
}

void	modify_flags(t_list *cmds)
{
	t_list	*curr;
	t_list	*new;

	curr = find_command(cmds);
	if (!curr)
	{
		new = ft_lstnew(ft_strdup(cmds->flags[0]));
		new->next = cmds->next;
		new->prev = cmds;
		cmds->next = new;
		new->next->prev = new;
		new->command = cmds->flags[0];
		new->flags = split_flags(cmds->flags);
		cmds->flags = NULL;
		new->type = 1;
	}
	else
		curr->flags = give_flags(curr, cmds);
}
