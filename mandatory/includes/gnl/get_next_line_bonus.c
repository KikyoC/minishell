/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:40:04 by tom               #+#    #+#             */
/*   Updated: 2024/10/24 17:40:36 by togauthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	fillbuffer(int fd, char **buffer)
{
	int	bytes;

	bytes = 0;
	*buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!*buffer)
	{
		return (-10);
	}
	bytes = read(fd, *buffer, BUFFER_SIZE);
	return (bytes);
}

char	*readfile(int fd, char *res)
{
	ssize_t	bytes;
	char	*buffer;
	char	*tmp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = fillbuffer(fd, &buffer);
		if (bytes < 0)
		{
			if (bytes != -10)
				free(buffer);
			free(res);
			return (NULL);
		}
		tmp = ft_strdup(res);
		free(res);
		res = ft_strjoin(tmp, buffer);
		free(tmp);
		free(buffer);
		if (ft_strchr(res, '\n'))
			break ;
	}
	return (res);
}

char	*ft_getline(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*update_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	res = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!res)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[i + 1])
		res[j++] = buffer[i++ + 1];
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	buffer[fd] = readfile(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_getline(buffer[fd]);
	buffer[fd] = update_buffer(buffer[fd]);
	return (line);
}
