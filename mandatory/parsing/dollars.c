
#include "../h_files/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	get_word(char *line, char *to_fill, t_iterate *iter)
{
	int	j;
	int	k;
	int	len;

	k = 0;
	j = iter->i;
	len = 0;
	while (ft_isalnum(line[++j]))
	{
		if (to_fill)
			to_fill[k++] = line[j];
		len++;
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
		}
	}
}

int	replace_dollars(char **env, char *line, char *final)
{
	t_iterate	iter;
	char		*word;
	t_texts		texts;

	texts.line = line;
	texts.final = final;
	texts.env = env;
	iter.i = 0;
	iter.j = 0;
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

// export lol=mdr

// echo $lol $loli $ '$lol' "$lol" '"$lol"' "'$lol'" $"lol" $'lol' "$"lol '$'lol $EMPTY $$ $lol.lol
