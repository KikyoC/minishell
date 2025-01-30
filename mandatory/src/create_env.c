#include "../h_files/minishell.h"

void	*destroy_node(t_env *node);
void	*destroy(t_env *env);

t_env	*create_node(char *str)
{
	int		i;
	int		j;
	t_env	*node;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_calloc(i + 1, sizeof(char));
	if (!node->name)
		return (destroy_node(node));
	j = i;
	while (--i > -1)
		node->name[i] = str[i];
	i = j;
	while (str[j])
		j++;
	node->content = ft_calloc(j + 1 - i, sizeof(char));
	if (!node->content)
		return (destroy_node(node));
	while (j-- - i > 1)
		node->content[j - i - 1] = str[j];
	return (node);
}

void	free_it_good(t_env *node, t_env *content, int append_mode)
{
	char	*tmp;

	tmp = node->content;
	if (append_mode)
	{
		node->content = ft_strjoin(tmp, content->content);
		free(content->content);
	}
	else
		node->content = content->content;
	free(tmp);
	free(content->name);
	free(content);
}

void	add_back(t_env **env, t_env *element, int append_mode)
{
	t_env	*node;
	size_t	len;

	len = ft_strlen(element->name);
	node = *env;
	while (node->next)
	{
		if (ft_strncmp(node->name, element->name, len) == 0)
		{
			free_it_good(node, element, append_mode);
			return ;
		}
		node = node->next;
	}
	if (ft_strncmp(node->name, element->name, len) == 0)
		free_it_good(node, element, append_mode);
	else
	{
		node->next = element;
		element->prev = node;
	}
}

t_env	*get_env(char **envp)
{
	int		i;
	t_env	*res;
	t_env	*node;

	i = 0;
	res = NULL;
	while (envp[i])
	{
		node = create_node(envp[i]);
		if (!node)
			return (destroy(res));
		if (!res)
			res = node;
		else
			add_back(&res, node, 0);
		i++;
	}
	return (res);
}
