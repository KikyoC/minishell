#include "../h_files/minishell.h"

char	*parse(char *str)
{
	int	i;

	i = 2;
	if (ft_strlen(str) == 2)
		return (NULL);
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (NULL);
	return (&str[i]);
}

int	args(char *str)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = -1;
	while (str[i])
	{
		if (str[i] == '"')
			in_quote = -in_quote;
		else if (str[i] == ' ' && in_quote == -1)
			return 1;
		i++;
	}
	return 0;
}

void	cd(char *str)
{
	char	*final;
	final = parse(str);
	if (args(final))
	{
		ft_putstr_fd("Minishell: too many arguments\n", 2);
		return ;
	}
	if (!final)
	{
		final = getenv("HOME");
		if (final && chdir(final))
			perror("Minishell");
	}
	if (chdir(final))
		perror("Minishell");
}
