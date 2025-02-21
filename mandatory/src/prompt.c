#include "../h_files/minishell.h"

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

char	*get_first_line(t_env **env)
{
	char	*username;
	char	*tmp;
	char	*res;

	username = find_env("USER", env);
	if (!username)
		username = "Unknown";
	tmp = ft_strjoin(BOLD BLUE ".---" CYAN "[" YELLOW, username);
	res = ft_strjoin(tmp, CYAN "]\n");
	if (tmp)
		free(tmp);
	return (res);
}

char	*get_second_line(t_env **env)
{
	char	*tmp;
	char	*res;
	char	*working_dir;

	working_dir = get_working_directory(env);
	if (!working_dir)
		working_dir = ft_strdup("Not found");
	tmp = ft_strjoin(BOLD BLUE "|---" CYAN "[" GREEN, working_dir);
	res = ft_strjoin(tmp, CYAN "]\n");
	if (tmp)
		free(tmp);
	if (working_dir)
		free(working_dir);
	return (res);
}

static void	free_all(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

char	*get_prompt(t_env **env)
{
	char	*first_line;
	char	*second_line;
	char	*third_line;
	char	*tmp;
	char	*res;

	first_line = get_first_line(env);
	second_line = get_second_line(env);
	third_line = ft_strdup(BOLD BLUE "`---" CYAN "[" GREEN
			"Segfault" CYAN "]" BLUE "-> " RESET);
	tmp = ft_strjoin(first_line, second_line);
	res = ft_strjoin(tmp, third_line);
	if (tmp)
		free(tmp);
	free_all(first_line, second_line, third_line);
	return (res);
}
