/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:04:57 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/12 13:55:25 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

char	choose_quote(char *line)
{
	if (line[0] == '\'' || line[0] == '"')
		return (reverse_quote(line[0]));
	return ('"');
}

void	fill_word_quote(t_iterate *iter, char *final, char *word, t_env *env)
{
	char	*tmp;

	printf("word : %s\n", word);
	tmp = find_env(word, &env);
	printf("word : %s, tmp : %s\n", word, tmp);
	iter->i += ft_strlen(word) + 1;
	free(word);
	if (!tmp)
		return ;
	cpy_text_add_quote(tmp, final, iter);
}

void	fill_word(t_iterate *iter, char *final, char *word, t_env *env)
{
	char	*tmp;

	tmp = find_env(word, &env);
	iter->i += ft_strlen(word) + 1;
	free(word);
	if (!tmp)
		return ;
	cpy_text(tmp, final, iter);
}
