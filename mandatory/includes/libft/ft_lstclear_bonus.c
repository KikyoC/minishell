/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:58:01 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/13 13:19:49 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !del)
		return (NULL);
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = next;
	}
	del(*lst);
	(*lst) = NULL;
	return (NULL);
}
