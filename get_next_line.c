/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/15 11:51:53 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	search_nl(char *s);

/*
** @brief read a line from a fildes
** @param fd file descriptor to read from
** @return line read from file descriptor
** @details check if line variable (NULL or '\0')
** @details is an empty string and no newline in buffer
** @details EOF reached or file is empty
*/
/* static char	*read_buffer(int fd, char *buffer, char *tmp, char *line)
{
	long long	b_read;

	b_read = BUFFER_SIZE;
	while (b_read > 0)
	{
		b_read = read(fd, tmp, BUFFER_SIZE);
		if (b_read == -1 || (b_read <= 0 && !buffer))
			return (free_buf(&buffer, 0));
		tmp[b_read] = '\0';
		buffer = copy_stash_buffer(buffer, tmp);
		if (search_nl(buffer))
		{
			line = parse_line(buffer);
			if (!line)
				return (free_buf(&buffer, 0));
			buffer = replace_buffer(buffer);
			return (line);
		}
	}
	return (free_buf(&buffer, 1));
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		tmp[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_buf(&buffer, 0));
	return (read_buffer(fd, buffer, tmp, line));
} */

/* char	*read_buffer(int fd, char *buffer)
{
	long long	b_read;
	char		tmp[BUFFER_SIZE + 1];
	char		*line;
	
	line = NULL;
	b_read = BUFFER_SIZE;
	while (b_read > 0)
	{
		b_read = read(fd, tmp, BUFFER_SIZE);
		if (b_read == -1 || (b_read <= 0 && !buffer))
			return (free_buf(&buffer));
		tmp[b_read] = '\0';
		buffer = copy_stash_buffer(buffer, tmp);
		if (search_nl(buffer))
		{
			line = parse_line(buffer);
			if (!line)
				return (free_buf(&buffer));
			buffer = rebuild_buffer(buffer);
			return (line);
		}
	}
	return (ret_line(&buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_buf(&buffer));
	return (read_buffer(fd, buffer));
} */
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
		return (free_buf(&buffer, 0));
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
