/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:41:44 by cmorel            #+#    #+#             */
/*   Updated: 2025/02/10 16:34:21 by xray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

void	print_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		printf("\b\b%s\n", split[i]);
}

// int	main(int argc, char **argv)
// {
// 	t_list	*lst;
// 	t_list	*curr;
//
// 	if (argc != 2)
// 		return (printf("merci de me donner un argument !\n"));
// 	lst = get_commands(argv[1]);
// 	curr = lst;
//
// 	int i = 0;
// 	while (curr)
// 	{
// 		printf("%d.\n\b command: %s\n",i,  curr->command);
// 		if (curr->flags)
// 			print_split(curr->flags);
// 		curr = curr->next;
// 		i++;
// 	}
// 	ft_lstclear(&lst, free);
// }

int main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*lst;
	t_list	*curr;
	int		i;

	(void)argc;
	(void)argv;
	while (1)
	{
		i = 0;
		line = readline("\e[0;36m──(\e[0;33m \e[1;32mSegfault\e[0;36m)──\e[1;36m> ");
		if (!line)
			break ;
		lst = get_commands(line, env);
		curr = lst;
		while (curr)
		{
			if (curr->type == 1)
				printf("%d. command : %s\n", i, curr->command);
			if (curr->type == 2)
				printf("%d. pipe : %s\n", i, curr->command);
			if (curr->type == 3)
				printf("%d. file : %s\n", i, curr->command);
			if (curr->type == 4)
				printf("%d. heredoc : %s\n", i, curr->command);
			if (curr->type == 5)
				printf("%d. redirect : %s\n", i, curr->command);
			if (curr->type == 6)
				printf("%d. heredoc param : %s\n", i, curr->command);
			if (curr->flags)
				print_split(curr->flags);
			curr = curr->next;
			i++;
		}
		ft_lstclear(&lst, free);
		if (ft_strnstr("exit", line, 4))
			break ;
		if (ft_strnstr("c", line, 1))
			clear(env);
		add_history(line);
		free(line);
	}
	ft_lstclear(&lst, free);
	rl_clear_history();
	return (0);
}
