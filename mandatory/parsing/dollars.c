
#include "../h_files/minishell.h"
#include <stdlib.h>

int	get_word(char *line, char *to_fill, int *i)
{
	int	j;
	int	k;
	int	len;

	k = 0;
	j = *i;
	len = 0;
	while (ft_isalnum(line[++j]))
	{
		if (to_fill)
			to_fill[k++] = line[j];
		j++;
		len++;
	}
	return (len);
}

char	*check_dollars(char *line, int *i, char *final)
{
	int		len;
	char	*word;

	if (line[(*i)] == '$')
	{
		len = get_word(line, NULL, i);
		if (!len)
			return (NULL);
		word = ft_calloc(len, sizeof(char));
		if (!word)
			return (NULL);
		get_word(line, word, i);
	}
	return (word);
}

void	handle_quotes(char *line, int *i, int code, char *final)
{
	char	*word;
	char	*tmp;

	while (line[++(*i)] != code)
	{
		word = check_dollars(line, i, final);
		if (word && code == '"')
		{
			tmp = getenv(word);
			free(word);
			if (!tmp)
				return ;
			cpy_text(tmp, line, i);
		}
	}
}

int	replace_dollars(char **env, char *line, char	*final)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
			handle_quotes(line, &i, '\'', final);
	}
	return (final);
}

// export lol=mdr

// echo $lol $loli $ '$lol' "$lol" '"$lol"' "'$lol'" $"lol" $'lol' "$"lol '$'lol $EMPTY $$ $lol.lol
