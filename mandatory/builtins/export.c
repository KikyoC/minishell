#include "../h_files/minishell.h"

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

t_env	*new_env(char *str, int append_mode)
{
	t_env	*res;

	res = ft_calloc(1, sizeof(t_env));
	if (!res)
		return (NULL);
	res = assign_node(str, append_mode, &res);
	if (!res)
		return (NULL);
	return (res);
}

void	add_if_required(t_env *element, t_env **env)
{
	t_env	*node;

	node = NULL;
	if (!element)
		return ;
	if (ft_strncmp("PWD", element->name, 4) == 0 && !find_env("OLDPWD", env))
	{
		node = ft_calloc(1, sizeof(t_env));
		if (!node)
			return ;
		node->name = ft_strdup("OLDPWD");
		node->content = ft_strdup(element->content);
	}
	else if (ft_strncmp("OLDPWD", element->name, 7) == 0 && !find_env("PWD", env))
	{
		node = ft_calloc(1, sizeof(t_env));
		if (!node)
			return ;
		node->name = ft_strdup("PWD");
		node->content = ft_strdup(element->content);
	}
	if (node && node->name && node->content)
		add_back(env, node, 0);
	else
		destroy_node(node);
}

int	export(t_list *lst, t_env **env)
{
	int		i;
	int		append_mode;
	t_env	*node;

	i = -1;
	if (lst->flags == NULL || lst->flags[0] == NULL)
		return (0);
	while (lst->flags[++i])
	{
		if (!parse(lst->flags[i], &append_mode))
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(lst->flags[i], 2);
			ft_putstr_fd(" cannot be parsed\n", 2);
			continue ;
		}
		node = new_env(lst->flags[i], append_mode);
		if (!node)
			continue ;
		add_if_required(node, env);
		add_back(env, node, append_mode);
	}
	return (0);
}
