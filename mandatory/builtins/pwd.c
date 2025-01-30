/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:53:08 by togauthi          #+#    #+#             */
/*   Updated: 2025/01/30 10:35:36 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

/* pwd:
*	Print the current path 
*/
void	pwd(void)
{
	char	*location;

	location = getcwd(NULL, PATH_MAX);
	printf("%s\n", location);
	free(location);
}
