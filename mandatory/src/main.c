/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:41:44 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/10 17:53:47 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

int main(void)
{
	char	*line;
	char	**path;

	path = get_paths(getenv("PATH"));
	for (int i = 0; path[i]; i++)
	{
		printf("path : %s\n", path[i]);
	}
	while (1)
	{
		line = readline("\e[0;36m──(\e[0;33m \e[1;32mSegfault\e[0;36m)──\e[1;36m> ");
		if (!line)
			break;
		if (ft_strnstr("pwd", line, 3))
			pwd();
		else if (ft_strnstr("exit", line, 5))
			return (0);
		else if (ft_strnstr("c", line, 1))
		{
			printf("test\n");
			clear(path);
			printf("test\n");
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
