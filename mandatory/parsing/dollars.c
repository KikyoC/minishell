/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:51:06 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 16:44:04 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../h_files/minishell.h"

int	get_word(char *line, char *to_fill, t_iterate *iter)
{
	int	j;
	int	k;
	int	len;

	k = 0;
	j = iter->i;
	len = 0;
	while (ft_isalpha(line[++j]) || line[j] == '_')
	{
		if (to_fill)
			to_fill[k++] = line[j];
		len++;
	}
	if (line[j] == '?')
	{
		if (to_fill)
			to_fill[k++] = line[j];
		len ++;
	}
	return (len);
}

char	*check_dollars(char *line, t_iterate *iter)
{
	int		len;
	char	*word;

	word = NULL;
	if (line[iter->i] == '$')
	{
		if (line[iter->i + 1] == '"' || line[iter->i + 1] == '\'')
		{
			iter->i++;
			return (NULL);
		}
		len = get_word(line, NULL, iter);
		if (!len)
			return (NULL);
		word = ft_calloc(len + 1, sizeof(char));
		if (!word)
			return (NULL);
		get_word(line, word, iter);
	}
	return (word);
}

void	handle_quotes(t_texts *texts, t_iterate *iter, int code)
{
	char	*word;
	int		count;

	count = 2;
	while (texts->line[iter->i] && count)
	{
		if (texts->line[iter->i] == code)
			count--;
		word = check_dollars(texts->line, iter);
		if (word && code == '"')
			fill_word(iter, texts->final, word, texts->env);
		else
		{
			if (texts->final)
				texts->final[iter->j] = texts->line[iter->i];
			(iter->i)++;
			(iter->j)++;
			if (word)
				free(word);
		}
	}
}

int	replace_dollars(t_env *env, char *line, char *final)
{
	t_iterate	iter;
	char		*word;
	t_texts		texts;

	texts.line = line;
	texts.final = final;
	texts.env = env;
	ft_bzero(&iter, sizeof(t_iterate));
	while (texts.line[iter.i])
	{
		if (texts.line[iter.i] == '\'' || texts.line[iter.i] == '"')
			handle_quotes(&texts, &iter, texts.line[iter.i]);
		word = check_dollars(texts.line, &iter);
		if (word)
			fill_word_quote(&iter, texts.final, word, texts.env);
		else if (!word && texts.line[iter.i])
		{
			if (texts.final)
				texts.final[iter.j] = texts.line[(iter.i)];
			(iter.j)++;
			(iter.i)++;
		}
	}
	return (iter.j);
}
