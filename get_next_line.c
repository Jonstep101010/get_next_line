/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/15 17:51:54 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*copy_stash_buffer(char *buf, char *stash);
static char	*replace_buffer(char *buffer);
static char	*parse_line(char *s);
static int	search_nl(char *s);

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
	static char		*buffer = NULL;
	char			stash[BUFFER_SIZE + 1];
	long long		bytes_read;

	bytes_read = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_buf(&buffer, 0));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, stash, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read <= 0 && !buffer))
			return (free_buf(&buffer, 0));
		stash[bytes_read] = '\0';
		buffer = copy_stash_buffer(buffer, stash);
		if (search_nl(buffer))
		{
			line = parse_line(buffer);
			if (!line)
				return (free_buf(&buffer, 0));
			return (buffer = replace_buffer(buffer), line);
		}
	}
	return (free_buf(&buffer, 1));
}

/*
** @brief free buffer and return value
** 
** @param buf buffer to free
** @param stash content to return
** @return char* duplicate of stash
*/
static char	*copy_stash_buffer(char *buf, char *stash)
{
	char	*copy;
	size_t	i;
	size_t	x;

	if (!buf && stash)
		return (ft_strdup(stash));
	i = -1;
	x = 0;
	if (!buf)
		buf = ft_strdup("");
	copy = (char *) malloc(ft_strlen(buf) + ft_strlen(stash) + 1);
	if (!copy)
		return (free(buf), NULL);
	while (buf[++i] != '\0')
		copy[i] = buf[i];
	while (stash[x] != '\0')
		copy[i++] = stash[x++];
	copy[i] = '\0';
	return (free_buf(&buf, 0), copy);
}

/*
** @brief parse line from buffer
** @param buf buffer to parse from
** @return char* line parsed from buffer
*/
static char	*parse_line(char *buf)
{
	char	*line;
	size_t	len;
	size_t	index;

	len = 0;
	if (!buf)
		return (free_buf(&buf, 0));
	while (buf[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (free_buf(&line, 0));
	index = 0;
	while (index < len + 1)
	{
		line[index] = buf[index];
		index++;
	}
	line[index] = '\0';
	return (line);
}

/*
** @brief copy content into new buffer, free old using free_buf
** implements parts of substr funcionality for copying buffer
** @param buffer to replace
** @return new buffer, NULL on failure
*/
static char	*replace_buffer(char *buffer)
{
	size_t	len;
	size_t	i;
	char	*n_buf;

	len = 0;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[len] != '\n')
		len++;
	if (buffer[len + 1] == '\0')
		return (free_buf(&buffer, 0));
	n_buf = malloc(sizeof(char) * (ft_strlen(buffer) - len));
	if (!n_buf)
		return (free_buf(&buffer, 0));
	while (buffer[len + i + 1])
	{
		n_buf[i] = buffer[len + i + 1];
		i++;
	}
	n_buf[i] = '\0';
	free_buf(&buffer, 0);
	return (n_buf);
}

/*
** @brief return 1 if newline in string
** 
** @param s buffer to search
** @return 0 no newline\
** @return 1 newline contained
*/
static int	search_nl(char *s)
{
	while (s && *s != '\0')
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}
