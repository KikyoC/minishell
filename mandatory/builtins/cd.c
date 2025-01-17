#include "../h_files/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void	cd(char *str)
{
	char	*final;
	final = parse(str);
	if (!final)
	{
		final = getenv("HOME");
		if (final && chdir(final))
			perror("Minishell");
	}
	if (chdir(final))
		perror("Minishell");
}
