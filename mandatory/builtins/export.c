#include "../h_files/minishell.h"

void	add_back(t_env **env, t_env *node, int append_mode);
t_env	*sort_env(t_env **env);

static char	*parse(char *line)
{
	int	i;

	i = 6;
	while (line[i] == ' ')
		i++;
	return (&line[i]);
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

t_env	*assign_node(char *str, int i, int append_mode, t_env **node)
{
	int		j;

	(*node)->name = ft_substr(str, 0, i - append_mode);
	j = i + 1;
	while (str[j])
		j++;	
	(*node)->content = ft_substr(str, i + 1, j);;
	if (!(*node)->name || !(*node)->content || ! (*node)->content[0])
		return (destroy_little((*node)));
	printf("Coucou");
	return (*node);
}

t_env	*new_env(char *str, int *append_mode)
{
	t_env	*res;
	int		i;

	i = 0;
	*append_mode = 0;
	res = ft_calloc(1, sizeof(t_env));
	if (!res)
		return (NULL);
	while (str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] != '=')
			return (destroy_little(res));
		else if (str[i] == '+')
			*append_mode = 1;
		if (str[i] == '\0')
			break;
		i++;
	}
	return (assign_node(str, i, *append_mode, &res));
}

void	print_env(t_env **env);
char	*parse_quotes(char *str, int multiple_args, t_env **env);
void	*destroy(t_env *env);

int	export(char *line, t_env **env)
{
	char	*parsed;
	char	*final;
	t_env	*node;
	t_env	*sort;
	int		append_mode;

	parsed = parse(line);
	if (!parsed)
		return (1);
	if (parsed[0] == '\0')
	{

		sort = sort_env(env);
		print_env(&sort);
		destroy(sort);
		return (1);
	}
	final = parse_quotes(parsed, 0, env);
	node = new_env(final, &append_mode);
	free(final);
	if (!node)
		return (1);
	add_back(env, node, append_mode);
	return (0);
}
