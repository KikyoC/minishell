#include "../h_files/minishell.h"
#include <stdlib.h>
#include <string.h>

void	add_back(t_env **env, t_env *node);

char	*parse(char *line)
{
	int	i;

	i = 6;
	while (line[i] == ' ')
		i++;
	return (ft_strdup(&line[i]));
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

t_env	*little_split(char *str)
{
	t_env	*res;
	size_t	i;
	size_t	j;

	res = ft_calloc(1, sizeof(t_env));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		if (str[i] == '\0')
			return (destroy_little(res));
		i++;
	}
	res->name = ft_substr(str, 0, i);
	i++;
	j = i;
	while (str[j] != ' ' && str[j])
		j++;
	res->content = ft_substr(str, i, j - i);
	if (!res->name || !res->content)
		return (destroy_little(res));
	return (res);
}

t_env	*find(t_env **env, char *str)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (strncmp(node->name, str, 6) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	export(char *line, t_env **env)
{
	char	*final;
	t_env	*node;

	final = parse(line);
	node = little_split(final);
	if (!node)
		return (1);
	add_back(env, node);
	
	node = find(env, "coucou");
	printf("The added node is now: %s=%s\n", node->name, node->content);
	return (0);
}
