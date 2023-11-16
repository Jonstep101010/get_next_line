/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/11/16 18:32:44 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*check_n_free(char *line, int i)
{
	char	*tmp;

	if (!line)
		return (NULL);
	while (line[i] != 0)
	{
		i++;
	}
	if (!ft_calloc(&tmp, i + 1))
		return (free(line), NULL);
	i = -1;
	while (line[++i] != 0)
	{
		tmp[i] = line[i];
	}
	free(line);
	return (tmp);
}

static char	*loop(int fd, char **line)
{
	static char		buffer[BUFFER_SIZE + 1];
	int				counter;
	int				i;

	counter = 0;
	while (counter <= BUFFER_SIZE && buffer[counter] && buffer[counter] != '\n')
		counter++;
	if (buffer[counter] == '\n' && !ft_calloc(line, BUFFER_SIZE + 1))
		return (NULL);
	if (buffer[counter] == '\n')
	{
		i = -1;
		while (buffer[++i] && buffer[i] != '\n')
			*(*line + i) = buffer[i];
		*(*line + i) = buffer[i];
		clean_buffer(buffer);
	}
	else
		read_line(buffer, fd, &counter, line);
	return (check_n_free(*line, 0));
}

char	*get_next_line(int fd)
{
	char	*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	return (loop(fd, &line));
}
