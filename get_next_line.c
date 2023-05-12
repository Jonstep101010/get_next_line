/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/12 21:09:16 by jschwabe         ###   ########.fr       */
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
	char			stash[BUFFER_SIZE + 1];
	long long		bytes_read;

	line = 0;
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
			line = current_line(buffer);
			if (!line)
				return (free_buf(&buffer, 0));
			return (buffer = new_buffer(buffer), line);
		}
	}
	return (free_buf(&buffer, 1));
}

char	*current_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stash)
		return (free_buf(&stash, 0));
	while (stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (free_buf(&line, 0));
	j = 0;
	while (j < i + 1)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

/*
** @brief copy line into new buffer, free old
** @param buffer to replace
** @return new buffer, NULL on failure
*/
char	*new_buffer(char *buffer)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\n')
		i++;
	if (buffer[i + 1] == '\0')
		return (free_buf(&buffer, 0));
	res = ft_substr(buffer, i + 1, ft_strlen(buffer));
	if (!res)
	{
		free_buf(&buffer, 0);
		return (NULL);
	}
	free_buf(&buffer, 0);
	return (res);
}

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

int	search_nl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
