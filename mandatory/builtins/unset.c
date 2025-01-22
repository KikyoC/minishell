#include "../h_files/minishell.h"
#include <string.h>

static char	*parse(char *line)
{
	int		i;
	int		j;
	int		skip;
	char	*final;

	i = 5;
	while (line[i] == ' ')
		i++;
	final = ft_calloc(ft_strlen(&line[i]) + 1, sizeof(char));
	if (!final)
		return (NULL);
	j = i;
	skip = 0;
	while (line[j] && line[j] != ' ')
	{
		if (line[j] == '"')
			skip++;
		else
			final[j - i - skip] = line[j];
		j++;
	}
	return (final);
}

int	unset(char *line, t_env **env)
{
	char	*final;
	t_env	*node;
	t_env	*to_delete;
	int		i;

	final = parse(line);
	if (!final)
		return (1);
	node = *env;
	i = ft_strlen(final);
	to_delete = NULL;
	while (node)
	{
		if (!node->next)
			break ;
		if (strncmp(final, node->next->name, i) == 0)
		{
			to_delete = node->next;
			node->next = to_delete->next;
			break ;
		}
		node = node->next;
	}
	if (to_delete)
	{
		free(to_delete->name);
		free(to_delete->content);
		free(to_delete);
	}
	free(final);
	return (0);
}
