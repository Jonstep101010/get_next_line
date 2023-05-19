/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/19 13:07:01 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** @brief read a line from a fildes
** check if line variable (NULL or '\0')
** is an empty string and no newline in buffer
** EOF reached or file is empty
** @param fd file descriptor to read from
** @return line read from file descriptor
*/
char	*get_next_line(int fd)
{
	char			*line;
	static char		buffer[BUFFER_SIZE + 1];
	int				counter;
	int				i;

	counter = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (buffer[counter] && buffer[counter] != '\n')
		counter++;
	if (counter <= BUFFER_SIZE && buffer[counter] == '\n')
	{
		line = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!line)
			return (NULL);
		ft_bzero(line, BUFFER_SIZE);
		i = -1;
		while (buffer[++i] != '\n')
			line[i] = buffer[i];
		line[i] = buffer[i];
		clean_buffer(buffer);
	}
	else
		read_line(buffer, fd, &counter, &line);
	return (check_n_free(line));
}

/*
** @brief copy from stash into line, including newline
** @param count for line index
** @param stash to copy from (tmp buffer for read data)
** @param line to copy into
*/
static void	parse_line(int *count, char *stash, char **line)
{
	int		i;

	i = -1;
	*count -= BUFFER_SIZE;
	while (stash[++i] && stash[i] != '\n' && i < BUFFER_SIZE)
		(*line)[*count + i] = stash[i];
	if (stash[i] == '\n')
		*(*line + *count + i) = '\n';
	i = -1;
}

/*
** @brief helper function to initialize line & copy buffer into it
** 
** @param line address
** @param count size of line
** @param buffer buffer to copy into line
** @return  
*/
static char	*callocate(char **line, int *count, char *buffer)
{
	int		i;

	i = -1;
	*line = malloc((*count + 1) * sizeof(char));
	if (!*line)
		return (NULL);
	ft_bzero(*line, *count);
	while (buffer[++i] != 0)
		*(*line + i) = buffer[i];
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
	int		b_r;
	int		i;

	ft_bzero(stash, BUFFER_SIZE);
	b_r = read(fd, stash, BUFFER_SIZE);
	if (b_r > 0)
		*count += BUFFER_SIZE;
	if (b_r < 0 || (b_r == 0 && *count == 0))
		return (ft_bzero(buf, BUFFER_SIZE), *line = NULL);
	if (stash[eol(stash)] == '\n' || (b_r == 0 && *count != 0))
	{
		if (!callocate(line, count, buf))
			return (NULL);
		i = -1;
		while (++i < BUFFER_SIZE)
			buf[i] = stash[i];
		clean_buffer(buf);
	}
	if (stash[eol(stash)] != '\n' && b_r != 0
		&& !read_line(buf, fd, count, line))
		return (NULL);
	if (*stash)
		parse_line(count, stash, line);
	return (*line);
}
