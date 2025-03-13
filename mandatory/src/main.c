/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:06:31 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/13 11:49:24 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"
#include <stdio.h>

int	g_signal_c = 0;

char	*ask_user(t_env **env)
{
	char	*prompt;
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		prompt = get_prompt(env);
		line = readline(prompt);
		if (g_signal_c == 130)
			exit_code(g_signal_c, env, -1, NULL);
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
	int		end;
	t_list	*ptr;

	line = ask_user(env);
	if (!line)
		return (-2);
	cmds = get_commands(line, *env);
	ptr = ((void *)cmds);
	end = run(&cmds, env);
	ft_lstclear(&ptr, free);
	return (end);
}

static int	setup(t_env **env, char **envp)
{
	*env = get_env(envp);
	if (!env)
		return (12);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	rl_outstream = stderr;
	exit_code(0, env, 0, NULL);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		state;
	int		exit_c;

	(void)argc;
	(void)argv;
	state = 0;
	env = NULL;
	if (setup(&env, envp))
		return (12);
	while (!state)
		state = core(&env);
	rl_clear_history();
	if (!parse_exit_code(NULL, find_env("?", &env)))
	{
		exit_c = 2;
		ft_putstr_fd("Exit code is not in good format\n", 2);
	}
	else
		exit_c = ft_atoi(find_env("?", &env));
	destroy(env);
	if ((state > 1 || state == -2) && isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	return (exit_c);
}
