/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/11/16 20:18:53 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*check_free(char *line)
{
	char	*tmp;
	int		i;

	if (!line)
		return (NULL);
	for (i = 0; line[i] != 0;)
		i++;
	if (ft_calloc(&tmp, i + 1))
	{
		for (int i = -1; line[++i] != 0;)
			tmp[i] = line[i];
		free(line);
		return (tmp);
	}
	return (free(line), NULL);
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
	return (check_free(*line));
}

char	*get_next_line(int fd)
{
	char	*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	return (loop(fd, &line));
}

void	clean_buffer(char *buffer)
{
	int	i;
	int	nl_index = 0;

	i = -1;
	while (buffer[nl_index] && buffer[nl_index] != '\n')
		nl_index++;
	buffer[nl_index] != '\n' ? buffer[nl_index++] = 0 : nl_index++;
	while (++i < BUFFER_SIZE - nl_index)
		buffer[i] = buffer[nl_index + i];
	buffer[i] = '\0';
}
