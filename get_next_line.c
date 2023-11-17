/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/11/17 18:12:32 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*check_free(char *line)
{
	char	*tmp;
	int		i;

	if (line)
	{
		for (i = 0; line[i] != '\0';)
			i++;
		if (!ft_calloc(&tmp, i + 1))
			return (free(line), NULL);
		for (i = -1; line[++i] != 0;)
			tmp[i] = line[i];
		free(line);
		return (tmp);
	}
	return (NULL);
}

int	copy_buffer(char *src, char *dst, int range)
{
	int	i;

	for (i = -1; ++i <= range;)
		dst[i] = src[i];
	return (i);
}

static char	*check_buffer(int fd, char **line)
{
	static char		buf[BUFFER_SIZE + 1];
	int				counter = 0;

	while (counter <= BUFFER_SIZE && buf[counter] && buf[counter] != '\n')
		counter++;
	if (buf[counter] == '\n')
	{
		if (!ft_calloc(line, BUFFER_SIZE + 1))
			return (NULL);
		copy_buffer(buf, *line, counter);
		clean_buffer(buf);
	}
	else
		read_line(buf, fd, &counter, line);
	return (check_free(*line));
}

char	*get_next_line(int fd)
{
	char	*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	return (check_buffer(fd, &line));
}

void	clean_buffer(char *buf)
{
	int	nl_index = 0;

	while (buf[nl_index] && buf[nl_index] != '\n')
		nl_index++;
	buf[nl_index] != '\n' ? buf[nl_index++] = 0 : nl_index++;
	copy_buffer(buf + nl_index, buf, BUFFER_SIZE - nl_index);
}
