/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/11/17 18:01:56 by jschwabe         ###   ########.fr       */
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

/**
 * @brief read line while tmp has no newline
 * @return line read from file descriptor /NULL
 */
char	*read_line(char *buf, int fd, int *count, char **line)
{
	char	tmp[BUFFER_SIZE + 1];
	int		rd;
	int		i;

	rd = read(fd, ft_memset(tmp, 0, BUFFER_SIZE), BUFFER_SIZE);
	if (rd > 0)
		*count += BUFFER_SIZE;
	if (rd < 0)
		return (ft_memset(buf, 0, BUFFER_SIZE));
	i = 0;
	while (i < BUFFER_SIZE && tmp[i] != '\n')
		i++;
	// data left in tmp or EOF and data in buffer
	if (tmp[i] == '\n' || (rd == 0 && *count != 0))
	{
		if (!ft_calloc(line, *count + 1))
			return (NULL);
		for (int x = -1; buf[++x] != '\0';)
			(*line)[x] = buf[x];
		copy_buffer(tmp, buf, BUFFER_SIZE - 1);
		clean_buffer(buf);
	}
	// data left in tmp or EOF and no data in buffer
	if (tmp[i] != '\n' && rd != 0 && !read_line(buf, fd, count, line))
		return (NULL);
	else if (rd > 0)
	{
		*count -= BUFFER_SIZE;
		// get index of newline
		for (i = -1; tmp[++i] != '\n' && i < BUFFER_SIZE;)
			;
		// copy tmp into line up to newline
		copy_buffer(tmp, *line + *count, i - 1);
		// copy newline into line
		if (tmp[i] == '\n')
			(*line)[*count + i] = '\n';
	}
	return (*line);
}
