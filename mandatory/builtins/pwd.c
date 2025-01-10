/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:39:16 by togauthi          #+#    #+#             */
/*   Updated: 2025/01/10 10:13:22 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "../includes/libft/libft.h"

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