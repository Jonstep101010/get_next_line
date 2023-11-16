/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/11/16 18:31:52 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = str;
	i = 0;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (str);
}

char	*ft_calloc(char **line, size_t size)
{
	*line = malloc(size * sizeof(char));
	if (!*line)
		return (NULL);
	return (ft_memset(*line, 0, size));
}

/*
** @brief copy content into start of buffer
** implements parts of substr funcionality for copying buffer
** @param buffer to replace
** @return new buffer, NULL on failure
*/
void	clean_buffer(char *buffer)
{
	int	i = 0;
	int	nl = 0;

	while (buffer[nl] && buffer[nl] != '\n')
		++nl;
	if (buffer[nl] != '\n')
		buffer[i++] = 0;
	else
		nl += 1;
	i -= 1;
	while (++i < BUFFER_SIZE - nl)
		buffer[i] = buffer[nl + i];
	buffer[i] = '\0';
}

/*
** @brief parse line from stash
**
** @param count
** @param line
** @param stash
** @return line
*/
static char	*parse_line(int *count, char **line, char *stash)
{
	int		i;

	i = -1;
	*count -= BUFFER_SIZE;
	while (stash[++i] && stash[i] != '\n' && i < BUFFER_SIZE)
		(*line)[*count + i] = stash[i];
	if (stash[i] == '\n')
		(*line)[*count + i] = '\n';
	return (*line);
}

/*
** @brief check if buffer has a newline
**
** @param stash
** @return true	- if newline in buffer
*/
static bool	nl(char *stash)
{
	int		i;

	i = -1;
	while (stash[++i] && stash[i] != '\n' && i < BUFFER_SIZE)
		;
	if (stash[i] == '\n')
		return (true);
	return (false);
}

/*
** @brief copy buffer into line and clean buffer
**
** @param line
** @param buffer
** @param stash
** @return
*/
static char	*copy_clean(char **line, int *count, char *buffer, char *stash)
{
	int		i;

	if (!ft_calloc(line, *count + 1))
		return (NULL);
	i = -1;
	while (buffer[++i] != 0)
		*(*line + i) = buffer[i];
	i = -1;
	while (++i < BUFFER_SIZE)
		buffer[i] = stash[i];
	clean_buffer(buffer);
	return (*line);
}

/*
** @brief read line while stash has no newline
**
** @param buf to copy into from stash
** @param fd to read from
** @param count for line index/read bytes
** @param line address to store line
** @return line read from file descriptor
*/
char	*read_line(char *buf, int fd, int *count, char **line)
{
	char	stash[BUFFER_SIZE + 1];
	int		rd;

	rd = read(fd, ft_memset(stash, 0, BUFFER_SIZE), BUFFER_SIZE);
	if (rd > 0)
		*count += BUFFER_SIZE;
	else if (rd < 0)
		return (ft_memset(buf, 0, BUFFER_SIZE), NULL);
	if ((((nl(stash) || (rd == 0 && *count != 0))
				&& (!copy_clean(line, count, buf, stash)))
			|| (!nl(stash) && rd != 0
				&& !read_line(buf, fd, count, line))))
		return (NULL);
	if (rd)
		parse_line(count, line, stash);
	return (*line);
}
