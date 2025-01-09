/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:13:37 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/21 17:37:59 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mal;

	if (size == 0 || nmemb == 0)
	{
		mal = malloc(0);
		return (mal);
	}
	mal = malloc(nmemb * size);
	if (!mal)
		return (NULL);
	ft_bzero(mal, nmemb * size);
	return (mal);
}
