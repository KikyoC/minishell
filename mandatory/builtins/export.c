#include "../h_files/minishell.h"

void	add_back(t_env **env, t_env *node);

static char	*parse(char *line)
{
	int		i;
	int		j;
	int		skip;
	char	*final;

	i = 6;
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

void	*destroy_little(t_env *node)
{
	if (!node)
		return (NULL);
	if (node->name)
		free(node->name);
	if (node->content)
		free(node->content);
	free(node);
	return (NULL);
}

t_env	*new_env(char *str)
{
	t_env	*res;
	int		i;
	int		j;

	i = 0;
	res = ft_calloc(1, sizeof(t_env));
	if (!res)
		return (NULL);
	while (str[i] != '=')
	{
		if (str[i] == '\0')
			return (destroy_little(res));
		i++;
	}
	res->name = ft_substr(str, 0, i);
	j = i + 1;
	while (str[j])
		j++;
	res->content = ft_substr(str, i + 1, j);
	if (!res->name || !res->content || ! res->content[0])
		return (destroy_little(res));
	return (res);
}

int	export(char *line, t_env **env)
{
	char	*final;
	t_env	*node;

	final = parse(line);
	if (!final)
		return (1);
	node = new_env(final);
	if (!node)
		return (1);
	add_back(env, node);	
	free(final);
	return (0);
}
