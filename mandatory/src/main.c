#include "../h_files/minishell.h"

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
