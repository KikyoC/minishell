#include "../h_files/minishell.h"

char	*parse_quotes(char *str, int multile_args, t_env **env);

void	write_echo(char **args, t_env **env)
{
	int		i;
	char	*to_print;

	i = 0;
	while (args[i])
	{
		to_print = parse_quotes(args[i], 1, env);
		if (!to_print)
			continue ;
		printf("%s", to_print);
		i++;
		if (args[i])
			printf(" ");
	}
}

void	echo(t_list *lst, t_env **env)
{
	int	new_line;

	new_line = 1;
	if (ft_strncmp(lst->flags[0], "-n", 3) == 0)
		new_line = 0;
	if (new_line)
	{
		write_echo(lst->flags, env);
		printf("\n");
	}
	else
		write_echo(&lst->flags[1], env);
}
