/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel <cmorel@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:01:59 by cmorel            #+#    #+#             */
/*   Updated: 2025/03/11 11:02:29 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../h_files/minishell.h"

void	write_env(char *actual, t_env **env, int fd, int *old);

char	*pre_join(char *s1, char *s2)
{
	char	*res;

	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	*fd_to_char(int fd)
{
	char	*res;
	char	*tmp;

	res = get_next_line(fd);
	while (res)
	{
		tmp = pre_join(res, get_next_line(fd));
		if (!tmp)
		{
			close(fd);
			return (NULL);
		}
		if (tmp == res)
			break ;
		tmp = res;
	}
	close(fd);
	return (res);
}

int	manage(char c, int q[2], int fd, int *i)
{
	if (c == '\'')
	{
		if (q[0] > 0 && fd > 0)
			write(fd, &c, 1);
		else
			q[1] = -q[1];
		(*i)++;
		return (1);
	}
	else if (c == '"')
	{
		if (q[1] > 0 && fd > 0)
			write(fd, &c, 1);
		else
			q[0] = -q[0];
		(*i)++;
		return (1);
	}
	return (0);
}

char	*parse_quotes(char *str, int multiple_args, t_env **env)
{
	int	p[2];
	int	q[2];
	int	i;

	if (pipe(p))
	{
		perror("Minishell");
		return (NULL);
	}
	q[0] = -1;
	q[1] = -1;
	i = -1;
	while (str[++i])
	{
		if (manage(str[i], q, p[1], &i))
			continue ;
		if (!multiple_args && str[i] == ' ' && q[0] < 0 && q[1] < 1)
			break ;
		if (str[i] == '$' && q[1] < 0)
			write_env(&str[i + 1], env, p[1], &i);
		else
			write(p[1], &str[i], 1);
	}
	close(p[1]);
	return (fd_to_char(p[0]));
}
