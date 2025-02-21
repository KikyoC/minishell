#include "../h_files/minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

t_env	*get_env(char **envp);
int		run(t_list **lst, t_env **env, int **pids);
void	*destroy(t_env *env);
int		g_signal_c = 0;

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
		return (ft_strdup("\e[0;36m──(\e[1;32mSegfault\e[0;36m)──\e[1;36m> \033[0m"));
	if (res)
		free(res);
	res = ft_strjoin(tmp, " \e[1;32mSegfault\e[0;36m)──\e[1;36m> \033[0m");
	free(tmp);
	if (!res)
		return (ft_strdup("\e[0;36m└─(\e[1;32mSegfault\e[0;36m)──\e[1;36m> \033[0m"));
	return (res);
}

int	core(t_env **env)
{
	char	*prompt;
	char	*line;
	t_list	*cmds;
	int		state;
	int		*pids;

	if (isatty(STDIN_FILENO))
	{
		prompt = get_prompt(env);
		line = readline(prompt);
		free(prompt);
	}
	else
		line = readline(NULL);
	if (!line)
		return (ENOMEM);
	cmds = get_commands(line, *env);
	state = run(&cmds, env, &pids);
	ft_lstclear(&cmds, free);
	if (state < 0)
		return (state);
	if (state == 0)
		return (-1);
	wait_all(pids, line, env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		state;
	int		exit_code;

	(void)argc;
	(void)argv;
	state = 0;
	signal(SIGQUIT, SIG_IGN);
	env = get_env(envp);
	if (!env)
	{
		perror("Minishell");
		return (1); 
	}
	rl_outstream = stderr;
	while (!state)
		state = core(&env);
	rl_clear_history();
	exit_code = ft_atoi(find_env("?", &env));
	destroy(env);
	if ((state > 0 || state == -2) && isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (state == -2 && exit_code)
		return (exit_code);
}
