/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:41:44 by cmorel            #+#    #+#             */
/*   Updated: 2025/02/03 18:00:29 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

t_env	*get_env(char **envp);
int		run(t_list **lst, t_env **env);
void	*destroy(t_env *env);

static char	*get_top(t_env **env)
{
	t_env	*node;
	char	*tmp;
	char	*res;

	node = *env;
	while (node)
	{
		if (ft_strncmp(node->name, "USER", 4) == 0)
			break ;
		node = node->next;
	}
	if (!node)
		return (NULL);
	tmp = ft_strjoin("\e[0;36m┌───", node->content);
	res = ft_strjoin(tmp, "\n");
	free(tmp);
	return (res);
}

static char	*get_working_directory(t_env **env)
{
	t_env	*node;
	char	*wd;
	int		i;
	char	*res;

	node = *env;
	i = 0;
	wd = getcwd(NULL, 50);
	if (!wd)
		return (NULL);
	while (node && ft_strncmp(node->name, "HOME", 4))
		node = node->next;
	if (!node)
		return (wd);
	while (wd[i] == node->content[i])
	{
		if (node->content[++i] == '\0')
		{
			wd[i - 1] = '~';
			res = ft_strdup(&wd[i - 1]);
			free(wd);
			return (res);
		}
	}
	return (wd);
}

char	*get_prompt(t_env **env)
{
	char	*res;
	char	*tmp;
	char	*wd;

	wd = get_working_directory(env);
	res = get_top(env);
	if (!res)
		tmp = ft_strjoin("\e[0;36m┌───Unknown\n", "\e[0;36m└─(\e[0;33m");
	else
		tmp = ft_strjoin(res, "\e[0;36m└─(\e[0;33m");
	if (res)
		free(res);
	res = tmp;
	tmp = ft_strjoin(res, wd);
	if (wd)
		free(wd);
	if (!tmp)
		return (ft_strdup("\e[0;36m└─(\e[1;32mSegfault\e[0;36m)──\e[1;36m> \033[0m"));
	if (res)
		free(res);
	res = ft_strjoin(tmp, " \e[1;32mSegfault\e[0;36m)──\e[1;36m> \033[0m");
	free(tmp);
	if (!res)
		return (ft_strdup("\e[0;36m└─(\e[1;32mSegfault\e[0;36m)──\e[1;36m> \033[0m"));
	return (res);
}

char	*parse_quotes(char *str, int multiple_args, t_env **env);

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_env	*env;
	// int		state;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	if (!env)
	{
		perror("Minishell: ");
		return (1);
	}
	while (1)
	{
		prompt = get_prompt(&env);
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		//TODO parsing and then execution
		t_list	*lst;
		lst = ft_calloc(1, sizeof(t_list));
		lst->flags = ft_calloc(4, sizeof(char *));
		lst->flags[0] = ft_strdup("-l");
		lst->flags[1] = ft_strdup("-a");
		lst->command = ft_strdup("ls");
		run(&lst, &env);
		ft_free_split(lst->flags);
		free(lst->command);
		free(lst);
		add_history(line);
		free(line);
	}
	destroy(env);
	rl_clear_history();
	return (0);
}
