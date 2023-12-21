/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/12/21 08:51:08 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i = 0;

	if (!str)
		return (0);
	for (i = 0; str[i] != '\0';)
		i++;
	return (i);
}

static void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = str;
	for (size_t i = 0; i < n; i++)
		ptr[i] = c;
	return (str);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	if (nitems && (nitems * size) / nitems != size)
		return (0);
	ptr = malloc(nitems * size);
	if (!ptr)
		return (0);
	return ((ft_memset(ptr, 0, nitems * size)));
}

/**
 * @brief Reads a line from a file descriptor.
 *
 * This function reads a line from the specified file descriptor and stores it in the line parameter.
 *
 * @param buf Buffer to store temporary data read from the file descriptor.
 * @param fd File descriptor to read from.
 * @param count Pointer to an integer representing the total number of characters read so far.
 * @param line Pointer to a string to store the read line.
 * @return The read line if successful, or NULL if an error occurs or the end of file is reached.
 */
char	*read_line(char *buf, int fd, int *count, char **line)
{
	char	tmp[BUFFER_SIZE + 1];
	int		rd;
	int		i;

	rd = read(fd, ft_memset(tmp, 0, BUFFER_SIZE), BUFFER_SIZE);
	if (rd > 0)
		*count += BUFFER_SIZE;
	else if (rd == -1)
		return (ft_memset(buf, 0, BUFFER_SIZE));//return NULL on read error
	i = 0;
	while (i < BUFFER_SIZE && tmp[i] != '\n')
		i++;
	// data left in tmp or EOF and data in buffer
	if (tmp[i] == '\n' || (rd == 0 && *count != 0))
	{
		*line = (char *) ft_calloc(sizeof(char), *count + 1);
		if (!*line)
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
