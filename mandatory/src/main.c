/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:41:44 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/10 18:10:09 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	**path;

	path = get_paths(getenv("PATH"));
	(void)argc;
	(void)argv;
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
			clear(env);
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
