/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:01:39 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/10 15:01:56 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

int	strings(char *input, char *command)
{
	int	i;

	i = 0;
	while ((input[i] && command[i]) && (input[i] == command[i]))
		i++;
	if (input[i] == '\n' && command[i] == '\0')
		return (1);
	return (0);
}
