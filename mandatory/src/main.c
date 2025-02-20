#include "../h_files/minishell.h"
#include <linux/limits.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

t_env	*get_env(char **envp);

int		run(t_list **lst, t_env **env, int **pids);
void	*destroy(t_env *env);


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

// static char	*get_top(t_env **env)
// {
// 	t_env	*node;
// 	char	*tmp;
// 	char	*res;
//
// 	node = *env;
// 	while (node)
// 	{
// 		if (ft_strncmp(node->name, "USER", 4) == 0)
// 			break ;
// 		node = node->next;
// 	}
// 	if (!node)
// 		return (NULL);
// 	res = ft_strjoin("\001\033[0;36m\002┌───", node->content);
// 	tmp = ft_strjoin(res, "───(");
// 	if (res)
// 		free(res);
// 	res = ft_strjoin(tmp, get_working_directory(env));
// 	if (tmp)
// 		free(tmp);
// 	tmp = ft_strdup("\001\033[36m\002==\001\033[1;36m\002> \001\033[0m\002");
// 	return (tmp);
// }

char *get_prompt(t_env **env)
{
    /* Color definitions */
    #define RESET   "\001\033[0m\002"
    #define BOLD    "\001\033[1m\002"
    #define RED     "\001\033[31m\002"
    #define GREEN   "\001\033[32m\002"
    #define YELLOW  "\001\033[33m\002"
    #define BLUE    "\001\033[34m\002"
    #define MAGENTA "\001\033[35m\002"
    #define CYAN    "\001\033[36m\002"

    /* Get required information */
    char	*working_dir;
    char	*username;
	char	*tmp;
	char	*res;

	working_dir = get_working_directory(env);
	username = find_env("USER", env);
	if (!username)
		username = "Unknown";
	if (!working_dir)
		working_dir = ft_strdup("Not found");
	tmp = ft_strjoin(BOLD BLUE ".---" CYAN "[" YELLOW, username);
	res = ft_strjoin(tmp, CYAN "]\n");
	if (tmp)
		free(tmp);
	tmp = ft_strjoin(res, BOLD BLUE "|---" CYAN "[" GREEN);
	if (res)
		free(res);
	res = ft_strjoin(tmp, working_dir);
	if (tmp)
		free(tmp);
	tmp = ft_strjoin(res, CYAN "]\n");
	if (res)
		free(res);
	res = ft_strjoin(tmp, BOLD BLUE "`---" CYAN "[" GREEN "Segfault" CYAN "]" BLUE "-> " RESET);
	if (tmp)
		free(tmp);
	return (res);




	char *line1 = ft_strdup(BOLD BLUE ".---" MAGENTA "[");
    char *line1_temp = ft_strjoin(line1, MAGENTA "]" BLUE "---" CYAN "[" YELLOW);
    char *line1_final = ft_strjoin(line1_temp, username);
    char *line1_complete = ft_strjoin(line1_final, CYAN "]" RESET "\n");
    char *line2 = ft_strjoin(BOLD BLUE "|---" GREEN "[", working_dir);
    char *line2_complete = ft_strjoin(line2, GREEN "]" RESET "\n");

    /* Final line with prompt symbol */
    char *final_prompt = ft_strdup(BOLD BLUE "`-" RED ">" RESET " ");

    char *temp1 = ft_strjoin(line1_complete, line2_complete);
    char *result = ft_strjoin(temp1, final_prompt);

    free(line1);
    free(line1_temp);
    free(line1_final);
    free(line1_complete);
    free(line2);
    free(line2_complete);
    free(final_prompt);
    free(temp1);
    free(working_dir);
    free(username);

    return (result);
}

char	*gett_prompt(t_env **env)
{
	char	*wd;
	char	*user;
	char	*tmp;
	char	*res;

	wd = get_working_directory(env);
	if (!wd)
		return (ft_strdup("==>"));
	user = find_env("USER", env);
	if (!user)
		user = ft_strdup("\001\033[34m\002(\001\033[36m\002Unknown");
	else
		user = ft_strjoin("\001\033[1;34m\002(\001\033[1;33m\002", user);
	res = ft_strjoin(user, "\001\033[34m\002)--(\001\033[1;33m\002");
	if (user)
		free(user);
	tmp = ft_strjoin(res, wd);
	if (res)
		free(res);
	if (wd)
		free(wd);
	res = ft_strjoin(tmp, "\001\033[34m\002)==> ");
	if (tmp)
		free(tmp);
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
