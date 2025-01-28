#include "../h_files/minishell.h"

void	add_back(t_env **env, t_env *node, int append_mode);
t_env	*sort_env(t_env **env);

char	*parse_quotes(char *str, int multiple_args, t_env **env);

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
	return (0);
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

t_env	*assign_node(char *str, int append_mode, t_env **node)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != '=')
		i++;
	(*node)->name = ft_substr(str, 0, i - append_mode);
	j = i + 1;
	while (str[j])
		j++;
	(*node)->content = ft_substr(str, i + 1, j);
	if (!(*node)->name || !(*node)->content || ! (*node)->content[0])
		return (destroy_little((*node)));
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
	while (str[i] != '=')
		i++;
	res = assign_node(str, append_mode, &res);
	tmp = parse_quotes(res->content, 0, env);
	if (!tmp)
		return (res);
	free(res->content);
	res->content = tmp;
	return (res);
}

static void	print_env(char *str, t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (ft_strncmp(node->name, str, ft_strlen(str)) == 0)
		{
			printf("%s=%s\n", node->name, node->content);
			return ;
		}
		node = node->next;
	}
	printf("NULL\n");
}

int	export(t_list *lst, t_env **env)
{
	int		i;
	int		append_mode;
	t_env	*node;
	char	*s;

	i = -1;
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
		s = ft_strdup(node->name);
		add_back(env, node, append_mode);
		print_env(s, env);
	}
	return (1);
}
