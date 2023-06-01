/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/06/01 21:57:50 by jschwabe         ###   ########.fr       */
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

	line = NULL;
	counter = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (counter <= BUFFER_SIZE && buffer[counter] && buffer[counter] != '\n')
		counter++;
	if (buffer[counter] == '\n')
	{
		if (!mallonize(&line, BUFFER_SIZE + 1))
			return (NULL);
		i = -1;
		while (buffer[++i] && buffer[i] != '\n')
			*(line + i) = buffer[i];
		*(line + i) = buffer[i];
		clean_buffer(buffer);
	}
	else
		read_line(buffer, fd, &counter, &line);
	return (check_n_free(line, 0));
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

	if (!mallonize(line, *count + 1))
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

	rd = read(fd, str_bzero(stash, BUFFER_SIZE), BUFFER_SIZE);
	if (rd > 0)
		*count += BUFFER_SIZE;
	else if (rd < 0)
		return (str_bzero(buf, BUFFER_SIZE), NULL);
	if ((((nl(stash) || (rd == 0 && *count != 0))
				&& (!copy_clean(line, count, buf, stash)))
			|| (!nl(stash) && rd != 0
				&& !read_line(buf, fd, count, line))))
		return (NULL);
	if (rd)
		parse_line(count, line, stash);
	return (*line);
}
