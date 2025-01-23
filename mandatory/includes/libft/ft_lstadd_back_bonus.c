/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:52:48 by cmorel            #+#    #+#             */
/*   Updated: 2025/01/23 12:30:45 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *n)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!lst)
		return ;
	if (*lst)
	{
		last->next = n;
		n->prev = last;
	}
	else
		*lst = n;
}
