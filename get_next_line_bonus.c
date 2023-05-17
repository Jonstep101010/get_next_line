/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/17 19:40:57 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
@brief read a line from a file descriptor
@param fd file descriptor to read from
@return line read from file descriptor
@details check if line variable (NULL or '\0')
@details is an empty string and no newline in buf
@details EOF reached or file is empty
*/
char	*get_next_line(int fd)
{
	char			*line;
	static char		buf[2048][BUFFER_SIZE + 1];
	int				count;

	count = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (buf[fd][count] && buf[fd][count] != '\n')
		count++;
	if (count <= BUFFER_SIZE && buf[fd][count] == '\n')
		callocate(&line, (int *) BUFFER_SIZE, buf[fd], 1);
	else
		read_line(buf[fd], fd, &count, &line);
	return (check_n_free(line));
}

/*
** @brief parsed malloc, NULL initialization copy processes & termination
** 
** @param line
** @param count 
** @param buffer
** @param marker for 
** @return char* 
*/
char	*callocate(char **line, int *count, char *buffer, int marker)
{
	int	i;

	i = -1;
	if (marker == 1)
	{
		*line = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!*line)
			return (NULL);
		ft_bzero(*line, BUFFER_SIZE);
		while (buffer[++i] != '\n')
			*(*line + i) = buffer[i];
		*(*line + i) = buffer[i];
		clean_buffer(buffer);
		return ((void *)line);
	}
	*line = malloc((*count + 1) * sizeof(char));
	if (!*line)
		return (NULL);
	ft_bzero(*line, *count);
	while (buffer[++i])
		*(*line + i) = buffer[i];
	return (*line);
}

char	*read_line(char *buf, int fd, int *count, char **line)
{
	char	stash[BUFFER_SIZE + 1];
	int		b_r;
	int		i;

	i = -1;
	ft_bzero(stash, BUFFER_SIZE);
	b_r = read(fd, stash, BUFFER_SIZE);
	if (b_r > 0)
		*count += BUFFER_SIZE;
	if (b_r < 0 || (b_r == 0 && *count == 0))
		return (ft_bzero(buf, BUFFER_SIZE), *line = NULL);
	if (stash[check_eol(stash)] == '\n' || (b_r == 0 && *count != 0))
	{
		if (!callocate(line, count, buf, 0))
			return (NULL);
		while (++i < BUFFER_SIZE)
			buf[i] = stash[i];
		clean_buffer(buf);
	}
	if (stash[check_eol(stash)] != '\n' && b_r != 0
		&& !read_line(buf, fd, count, line))
		return (NULL);
	if (*stash)
		copy_line(count, stash, line);
	return (*line);
}

/*copy stash to line for BUFFER_SIZE*/
void	copy_line(int *count, char *stash, char **line)
{
	int	i;

	i = -1;
	*count -= BUFFER_SIZE;
	while (stash[++i] && i < BUFFER_SIZE && stash[i] != '\n')
		*(*line + *count + i) = stash[i];
	if (stash[i] == '\n')
		*(*line + *count + i) = stash[i];
}

/* char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	size;

	size = ft_strlen(s) + 1;
	copy = malloc(size);
	if (!copy)
		return (0);
	while (size-- && (copy))
		copy[size] = s[size];
	return (copy);
} */

/* void	*free_buf(char **buf, int returnval)
{
	char	*line;

	if (!*buf)
		return (NULL);
	if (returnval == 1)
	{
		line = ft_strdup(*buf);
		free(*buf);
		*buf = NULL;
		return (line);
	}
	if (returnval == -1)
	{
		return (*buf = NULL);
	}
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	return (NULL);
} */

/* char	*new_buf(char *buf)
{
	int			i;
	int			n;
	char		*new_buf;

	i = 0;
	n = 0;
	if (!buf)
		return (NULL);
	while (buf[n] && buf[n] != '\n')
		n++;
	if (buf[n] == '\0')
		return (free(buf), NULL);
	n++;
	new_buf = malloc(sizeof(char) * ft_strlen(buf) - n + 1);
	if (!new_buf)
		return (free(buf), NULL);
	while (buf[n])
		new_buf[i++] = buf[n++];
	new_buf[i] = '\0';
	free(buf);
	return (new_buf);
} */

/*
char	*current_line(char *s)
{
	char	*line;
	size_t	i;

	i = 0;
	line = NULL;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = s[i];
	if (line[i] == '\n')
		line[++i] = '\0';
	return (line);
} */