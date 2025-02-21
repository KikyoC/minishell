#include "../h_files/minishell.h"

void	update_code(int code, t_env	**env)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return ;
	node->name = ft_strdup("?");
	node->content = ft_itoa(code);
	if (!node->name || !node->content)
		destroy_node(node);
	add_back(env, node, 0);
}

int	wait_all(int *pids, char *line, t_env **env)
{
	int	state;
	int	i;

	state = 0;
	i = 0;
	add_history(line);
	free(line);
	while (pids[i] && i < 10)
	{
		waitpid(pids[i], &state, 0);
		i++;
	}
	free(pids);
	update_code(state, env);
	return (state);
}

void	add_pid_back(int *pids, int pid)
{
	int	i;

	if (pid <= 0)
		return ;
	i = 0;
	while (pids[i])
		i++;
	pids[i] = pid;
}
