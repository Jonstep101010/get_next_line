/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2024/02/19 23:05:25 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <limits.h>

static char	*check_free(char *line)
{
	char	*tmp;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
		++i;
	tmp = (char *) ft_calloc(sizeof(char), i + 1);
	if (!tmp)
		return (free(line), NULL);
	ft_memcpy(tmp, line, i);
	free(line);
	return (tmp);
}

static char	*read_line(char *buf, int fd, int *counter, char **line);
static void	clean_buffer(char *buf);

char	*get_next_line(int fd)
{
	char			*line;
	static char		buf[NUM_FD][BUFFER_SIZE + 1];
	int				counter;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	counter = 0;
	while (counter <= BUFFER_SIZE && buf[fd][counter])
	{
		if (buf[fd][counter] == '\n')
		{
			line = (char *) ft_calloc(sizeof(char), BUFFER_SIZE + 1);
			if (!line)
				return (NULL);
			ft_memcpy(line, buf[fd], counter + 1);
			clean_buffer(buf[fd]);
			return (check_free(line));
		}
		counter++;
	}
	if (buf[fd][counter] != '\n')
		read_line(buf[fd], fd, &counter, &line);
	return (check_free(line));
}

static void	clean_buffer(char *buf)
{
	int	nl_index;

	nl_index = index_of(buf, '\n', INT_MAX);
	if (buf[nl_index] != '\n')
		buf[nl_index] = 0;
	else
		nl_index++;
	ft_memcpy(buf, (buf + nl_index), (BUFFER_SIZE - nl_index) + 1);
}

static void	read_success(char *tmp, char **line, int *counter)
{
	int	i;

	*counter -= BUFFER_SIZE;
	i = index_of(tmp, '\n', BUFFER_SIZE);
	ft_memcpy((*line + *counter), tmp, i);
	if (tmp[i] == '\n')
		(*line)[*counter + i] = '\n';
}

/**
 * @brief Reads a line from a file descriptor.
 *
 * This function reads a line from the specified file
 * descriptor and stores it in the line parameter.
 *
 * @param buf Buffer to store temporary data read from the file descriptor.
 * @param fd File descriptor to read from.
 * @param counter Pointer to an integer representing the total
 * number of characters read so far.
 * @param line Pointer to a string to store the read line.
 * @return The read line if successful, or NULL if an error occurs
 * or the end of file is reached.
 */
static char	*read_line(char *buf, int fd, int *counter, char **line)
{
	char	tmp[BUFFER_SIZE + 1];
	int		rd;
	int		i;

	rd = read(fd, ft_memset(tmp, 0, BUFFER_SIZE), BUFFER_SIZE);
	if (rd == -1)
		return (ft_memset(buf, 0, BUFFER_SIZE));
	if (rd > 0)
		*counter += BUFFER_SIZE;
	i = index_of(tmp, '\n', BUFFER_SIZE);
	if (tmp[i] == '\n' || (rd == 0 && *counter != 0))
	{
		*line = (char *) ft_calloc(sizeof(char), *counter + 1);
		if (!*line)
			return (NULL);
		ft_strlcpy(*line, buf, *counter + 1);
		ft_memcpy(buf, tmp, BUFFER_SIZE);
		clean_buffer(buf);
	}
	if (tmp[i] != '\n' && rd != 0 && !read_line(buf, fd, counter, line))
		return (NULL);
	else if (rd > 0)
		read_success(tmp, line, counter);
	return (*line);
}
