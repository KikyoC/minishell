

#include "../h_files/minishell.h"

int	check_errors(char *command)
{
	int	i;
	int	before;
	int	sign;
	int	quote;
	int	double_quote;
	int found;

	quote = 1;
	double_quote = 1;
	reset(&before, &sign);
	i = -1;
	while (command[++i])
	{
		if (command[i] == '\'')
			quote *= -1;
		else if (command[i] == '"')
			double_quote *= -1;
		if (double_quote > 0 && quote > 0)
		{
			if (!before && ft_isalpha(command[i]))
				before = 1;
			else if (before && sign != 2)
				sign += is_operator(command[i], sign);
			if (sign >= 1 && ft_isalpha(command[i]))
				found = reset(&before, &sign);
		}
		if (sign < 0)
			return (-2);
	}
	if (found == 1 && sign != 0)
		return (-1);
	else
		return (1);
}

int main (int argc, char **argv)
{
	if (argc < 2)
		return (printf("Merci de me donner une chaine de char \n"));
	printf("%d\n",check_errors(argv[1]));
}
