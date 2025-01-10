/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:41:44 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/10 14:11:39 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char	**ft_split(char *str, char *splitter);

void	printf_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		printf("%s|\n", split[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("\e[0;36m──(\e[0;33m \e[1;32mSegfault\e[0;36m)──\e[1;36m> ");
		if (!line)
			break;
		printf_split(ft_split(line, argv[1]));
		//He we should do something with the line
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
