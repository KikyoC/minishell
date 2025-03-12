/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:08:57 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:08:59 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

int	expand_here(char *flag, char *ptr, t_env *env)
{
	t_iterate	iter;
	char		*word;

	ft_bzero(&iter, sizeof(t_iterate));
	while (flag[iter.i])
	{
		word = check_dollars(flag, &iter);
		if (word)
			fill_word(&iter, ptr, word, env);
		else
		{
			if (ptr)
				ptr[iter.j] = flag[(iter.i)];
			(iter.j)++;
			(iter.i)++;
		}
	}
	return (iter.j);
}

void	heredoc_expand(char **flags, t_env *env)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	tmp = NULL;
	while (flags[i])
	{
		len = expand_here(flags[i], NULL, env);
		tmp = ft_calloc(len + 2, sizeof(char));
		if (!tmp)
			return ;
		expand_here(flags[i], tmp, env);
		free(flags[i]);
		flags[i] = tmp;
		i++;
	}
}
