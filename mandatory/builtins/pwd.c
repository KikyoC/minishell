/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:39:16 by togauthi          #+#    #+#             */
/*   Updated: 2025/01/10 14:55:46 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

/* pwd:
*	Print the current path 
*/
void	pwd(void)
{
	char	*location;

	location = ft_calloc(PATH_MAX + 1, sizeof(char));
	getcwd(location, PATH_MAX);
	printf("%s\n", location);
}
