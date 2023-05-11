/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/11 18:41:11 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** @brief read a line from a file descriptor
** @param fd file descriptor to read from
** @return line read from file descriptor
** @details check if line variable (NULL or '\0')
** @details is an empty string and no newline in buffer
** @details EOF reached or file is empty
*/
char	*get_next_line(int fd)
{
	char			*line;
	static char		*buffer = NULL;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = read_line(buffer, fd);
	if (buffer == NULL)
		return (NULL);
	line = current_line(buffer);
	if (*line == '\0' && !ft_strchr(buffer, '\n'))
	{
		free(line);
		buffer = new_buffer(buffer);
		return (NULL);
	}
	buffer = new_buffer(buffer);
	return (line);
}

/*
** @brief read a line from fildes, protect against read fail
** @param buffer 
** @param fd 
** @return char* 
*/
char	*read_line(char *buffer, int fd)
{
	char	*stash;
	int		bytes_read;

	bytes_read = 1;
	stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!stash)
		return (NULL);
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, stash, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buffer);
			stash = NULL;
			return (NULL);
		}
		stash[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, stash);
		if (!buffer)
			return (free(stash), NULL);
	}
	return (free(stash), buffer);
}

/*copy from string until end or \n*/
char	*current_line(char *s)
{
	char	*line;
	size_t	i;

	i = 0;
	line = NULL;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = s[i];
	if (line[i] != '\0')
		line[++i] = '\0';
	return (line);
}

/*
** @brief copy line into new buffer, free old
** @param buffer to replace
** @return new buffer, NULL on failure
*/
char	*new_buffer(char *buffer)
{
	int			i;
	int			n;
	char		*new_buffer;

	i = 0;
	n = 0;
	// if (!buffer)
	// 	return (NULL);
	while (buffer[n] != '\0' && buffer[n] != '\n')
		n++;
	if (buffer[n] == '\0')
		return (free(buffer), NULL);
	new_buffer = malloc(ft_strlen(buffer) - n + 1);
	if (!new_buffer)
		return (free(buffer), NULL);
	n++;
	while (buffer[n] != '\0')
		new_buffer[i++] = buffer[n++];
	new_buffer[i] = '\0';
	return (free(buffer), new_buffer);
}
