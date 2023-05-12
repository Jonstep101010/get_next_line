/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:11:24 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/13 01:31:17 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	search_nl(char *s);

/*
** @brief read a line from a fildes
** @param fd file descriptor to read from
** @return line read from file descriptor
** @details check if line variable (NULL or '\0')
** @details is an empty string and no newline in buffer
** @details EOF reached or file is empty
*/
char	*get_next_line(int fd)
{
	char			*line;
	static char		*buffer[2048];
	char			*stash;
	long long		bytes_read;

	bytes_read = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_buf(&buffer[fd], 0));
	stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, stash, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read <= 0 && !buffer[fd]))
			return (free_buf(&buffer[fd], 0));
		stash[bytes_read] = '\0';
		buffer[fd] = copy_stash_buffer(buffer[fd], stash);
		if (search_nl(buffer[fd]))
		{
			line = parse_line(buffer[fd]);
			if (!line)
				return (free_buf(&buffer[fd], 0));
			return (buffer[fd] = replace_buffer(buffer[fd]), line);
		}
	}
	return (free_buf(&buffer[fd], 1));
}

/*
** @brief parse line from buffer
** @param buf buffer parse from
** @return char* line parsed from buffer
*/
char	*parse_line(char *buf)
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
** @param buffer to replace
** @return new buffer, NULL on failure
*/
char	*replace_buffer(char *buffer)
{
	size_t	i;
	char	*n_buf;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\n')
		i++;
	if (buffer[i + 1] == '\0')
		return (free_buf(&buffer, 0));
	n_buf = ft_substr(buffer, i + 1, ft_strlen(buffer));
	if (!n_buf)
	{
		free_buf(&buffer, 0);
		return (NULL);
	}
	free_buf(&buffer, 0);
	return (n_buf);
}

/*
** @brief handle buffer freeing and return values
** 
** @param buffer address of buffer to free
** @param returnval 1 to return buffer, 0 to free buffer
** @return char* if line return is expected\
** @return void* if free or buffer == NULL
*/
void	*free_buf(char **buffer, int returnval)
{
	char	*line;

	if (!*buffer)
		return (NULL);
	if (returnval == 0)
	{
		if (*buffer)
		{
			free(*buffer);
			*buffer = NULL;
		}
		return (NULL);
	}
	else if (returnval == 1)
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (line);
	}
	return (NULL);
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
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}
