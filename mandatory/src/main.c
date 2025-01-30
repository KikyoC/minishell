/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:41:44 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/30 11:57:21 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

t_env	*get_env(char **envp);

char	*get_prompt(t_env **env)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		
		node = node->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;

	env = get_env(envp);
	if (!env)
	{
		perror("Minishell: ");
		return (1);
	}
	while (1)
	{
		line = readline("\e[0;36m──(\e[0;33m \e[1;32mSegfault\e[0;36m)──\e[1;36m> ");
		if (!line)
			break;
		
		//TODO parsing and then execution
		add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
