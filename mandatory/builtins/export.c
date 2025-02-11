#include "../h_files/minishell.h"

void	add_back(t_env **env, t_env *node, int append_mode);
t_env	*sort_env(t_env **env);

char	*parse_quotes(char *str, int multiple_args, t_env **env);
int		print_export(t_env **env);
void	*destroy_node(t_env *node);
void	*destroy(t_env *env);

static int	parse(char *str, int *append_mode)
{
	int	i;
	int	part;

	i = 0;
	part = 0;
	*append_mode = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			*append_mode = 1;
			return (ft_isprint(str[i + 2]) > 0);
		}
		else if (str[i] == '=')
			return (ft_isprint(str[i + 1]) > 0);
		i++;
	}
	return (1);
}

t_env	*assign_node(char *str, int append_mode, t_env **node)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	(*node)->name = ft_substr(str, 0, i - append_mode);
	i += (str[i] != '\0');
	j = i;
	while (str[j])
		j++;
	(*node)->content = ft_substr(str, i, j);
	if (!(*node)->name || (j != i && ((*node)->content == NULL
				|| (*node)->content[0] == '\0')))
		return (destroy_node(*node));
	return (*node);
}

t_env	*new_env(char *str, int append_mode, t_env **env)
{
	t_env	*res;
	int		i;
	char	*tmp;

	i = 0;
	res = ft_calloc(1, sizeof(t_env));
	if (!res)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	res = assign_node(str, append_mode, &res);
	if (!res)
		return (NULL);
	if (res->content)
	{
		tmp = parse_quotes(res->content, 0, env);
		if (!tmp)
			return (res);
		free(res->content);
		res->content = tmp;
	}
	return (res);
}

int	print_export(t_env **env)
{
	t_env	*sorted;
	t_env	*node;

	sorted = sort_env(env);
	if (!sorted)
		return (1);
	node = sorted;
	while (node)
	{
		printf("declare -x %s", node->name);
		if (node->content && node->content[0])
			printf("=\"%s\"", node->content);
		printf("\n");
		node = node->next;
	}
	destroy(sorted);
	return (0);
}

int	export(t_list *lst, t_env **env)
{
	int		i;
	int		append_mode;
	t_env	*node;

	i = -1;
	if (lst->flags == NULL || lst->flags[0] == NULL)
		return (print_export(env));
	while (lst->flags[++i])
	{
		if (!parse(lst->flags[i], &append_mode))
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(lst->flags[i], 2);
			ft_putstr_fd(" cannot be parsed\n", 2);
			continue ;
		}
		node = new_env(lst->flags[i], append_mode, env);
		if (!node)
			continue ;
		add_back(env, node, append_mode);
	}
	return (0);
}
