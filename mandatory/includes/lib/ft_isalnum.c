/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:32:26 by cmorel            #+#    #+#             */
/*   Updated: 2024/10/09 11:59:34 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	int	returned_value;

	returned_value = 8;
	if (c >= '0' && c <= '9' )
		return (returned_value);
	else if (c >= 'a' && c <= 'z')
		return (returned_value);
	else if (c >= 'A' && c <= 'Z')
		return (returned_value);
	return (0);
}
