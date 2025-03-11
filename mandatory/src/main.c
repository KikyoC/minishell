/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:06:31 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:06:32 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

int	g_signal_c = 0;

char	*ask_user(t_env **env)
{
	char	*prompt;
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		prompt = get_prompt(env);
		line = readline(prompt);
		free(prompt);
	}
	else
		line = readline(NULL);
	return (line);
}

int	core(t_env **env)
{
	char	*line;
	t_list	*cmds;
	int		state;
	int		*pids;

	line = ask_user(env);
	if (!line)
		return (-2);
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

static void	setup(t_env **env)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	rl_outstream = stderr;
	exit_code(0, env, 0, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		state;
	int		exit_c;

	(void)argc;
	(void)argv;
	state = 0;
	env = get_env(envp);
	if (!env)
		return (12);
	setup(&env);
	while (!state)
		state = core(&env);
	rl_clear_history();
	if (!parse_exit_code(NULL, find_env("?", &env)))
		exit_c = 2;
	else
		exit_c = ft_atoi(find_env("?", &env));
	destroy(env);
	if ((state > 0 || state == -2) && isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (state == -2 && exit_c)
		return (exit_c);
}
