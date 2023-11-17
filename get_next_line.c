/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/11/17 11:30:28 by jschwabe         ###   ########.fr       */
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

int	copy_buffer(char *src, char *dst, int range)
{
	int	i;

	for (i = -1; ++i <= range;)
		dst[i] = src[i];
	return (i);
}

static char	*loop(int fd, char **line)
{
	static char		buffer[BUFFER_SIZE + 1];
	int				counter;

	counter = 0;
	while (counter <= BUFFER_SIZE && buffer[counter] && buffer[counter] != '\n')
		counter++;
	if (buffer[counter] == '\n')
	{
		if (!ft_calloc(line, BUFFER_SIZE + 1))
			return (NULL);
		copy_buffer(buffer, *line, counter);
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
	int	nl_index = 0;

	while (buffer[nl_index] && buffer[nl_index] != '\n')
		nl_index++;
	buffer[nl_index] != '\n' ? buffer[nl_index++] = 0 : nl_index++;
	copy_buffer(buffer + nl_index, buffer, BUFFER_SIZE - nl_index);
}
