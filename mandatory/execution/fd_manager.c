/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:10:10 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/12 18:03:44 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

void	close_node(t_list *lst)
{
	if (!lst)
		return ;
	if (lst->input > 2)
	{
		close(lst->input);
	}
	if (lst->output > 2)
	{
		close(lst->output);
	}
}
