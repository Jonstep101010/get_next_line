/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/11/16 20:25:16 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = str;
	for (size_t i = 0; i < n; i++)
		ptr[i] = c;
	return (str);
}

char	*ft_calloc(char **line, size_t size)
{
	*line = malloc(size * sizeof(char));
	if (!*line)
		return (NULL);
	return (ft_memset(*line, 0, size));
}

static char	*parse_line(int *count, char **line, char *stash)
{
	int		i;

	*count -= BUFFER_SIZE;
	for (i = -1; stash[++i] != '\n' && i < BUFFER_SIZE;)
		(*line)[*count + i] = stash[i];
	if (stash[i] == '\n')
		(*line)[*count + i] = '\n';
	return (*line);
}

static char	*copy_clean(char **line, int *count, char *buffer, char *stash)
{
	if (!ft_calloc(line, *count + 1))
		return (NULL);
	// copy buffer into line
	for (int i = -1; buffer[++i] != 0;)
		(*line)[i] = buffer[i];
	// copy stash into buffer
	for (int i = -1; ++i < BUFFER_SIZE;)
		buffer[i] = stash[i];
	clean_buffer(buffer);
	return (*line);
}

/**
 * @brief read line while stash has no newline
 * @return line read from file descriptor /NULL
 */
char	*read_line(char *buf, int fd, int *count, char **line)
{
	char	stash[BUFFER_SIZE + 1];
	int		rd;
	int		i;

	rd = read(fd, ft_memset(stash, 0, BUFFER_SIZE), BUFFER_SIZE);
	if (rd > 0)
		*count += BUFFER_SIZE;
	if (rd < 0)
		return (ft_memset(buf, 0, BUFFER_SIZE));
	i = 0;
	while (i < BUFFER_SIZE && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i = -1;
	// data left in stash or EOF and data in buffer
	if ((i == -1 || (rd == 0 && *count != 0))
		&& !copy_clean(line, count, buf, stash))
		return (NULL);
	// data left in stash or EOF and no data in buffer
	else if (i >= 0 && rd != 0 && !read_line(buf, fd, count, line))
		return (NULL);
	else if (rd > 0)
		parse_line(count, line, stash);
	return (*line);
}
