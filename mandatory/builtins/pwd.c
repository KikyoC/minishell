/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:53:08 by togauthi          #+#    #+#             */
/*   Updated: 2025/02/13 09:40:35 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

/* pwd:
*	Print the current path 
*/
int	pwd(t_list *cmd, t_env ** env)
{
	char	*location;

	(void)env;
	location = getcwd(NULL, PATH_MAX);
	ft_putstr_fd(location, cmd->output);
	ft_putchar_fd('\n', cmd->output);
	free(location);
	return (0);
}
