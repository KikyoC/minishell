/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:49:52 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/16 09:36:26 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*new_content;
	void	*cont;

	if (!lst || !f || !del)
		return (NULL);
	result = NULL;
	while (lst)
	{
		new_content = NULL;
		cont = f(lst->content);
		if (cont)
			new_content = ft_lstnew(cont);
		if (!new_content)
		{
			del(cont);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, new_content);
		lst = lst->next;
	}
	return (result);
}
