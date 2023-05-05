/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/05 17:42:21 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(char *buffer, int fd)
{
	int		bytes_read;
	char		*stash;
	int				i;

	i = 0;
	stash = (char *) malloc(BUFFER_SIZE + 1);
	if (!stash)
		return (NULL);
	bytes_read = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n' && i < BUFFER_SIZE)
	{
		i++;
	}
	bytes_read = read(fd, stash, BUFFER_SIZE);
	if (bytes_read == 0)
		return (free(stash), buffer);
	
	//append stash to buffer
	if (!buffer)
		return (free(stash), NULL);
	buffer = ft_strjoin(stash, buffer);
	return (free(stash), buffer);
}

char	*new_buffer(char *buffer)
{
	int			i;
	int			n;
	int			buffer_len;
	char	*new_buffer;

	i = 0;
	n = 0;
	while (buffer[n] && buffer[n] != '\n')
		n++;
	buffer_len = ft_strlen(buffer);
	if (buffer[n + 1] == '\n')
		new_buffer = malloc(sizeof(char) * (buffer_len - n));
	if (buffer[n] == '\0')
	{
		free(buffer);
		return (0);
	}
	while (buffer[n])
	{
		new_buffer[i] = buffer[n];
		i++;
		n++;
	}
	new_buffer[i] = '\0';
	free(buffer);
	return (new_buffer);
}

/*copy from string until end or \n*/
char	*current_line(char *s)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = (char *) malloc(i + 1);
	if (!line)
		return (0);
	while (s[i + 1] != '\0' && s[i + 1] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}


/*
@brief read a line from a file descriptor
@param fd file descriptor to read from
@reaturn line read from file descriptor
*/
char	*get_next_line(int fd)
{
	char			*line;
	static char		*buffer;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buffer = read_line(buffer, fd);
	// printf("\n%s\n", buffer);
	if (!buffer)
		return (0);
	line = current_line(buffer);
	buffer = new_buffer(buffer);
	//free until buffer - return after newline
	free(line);
	return (buffer);
}

/* int	main(void)
{
	int	fd;
	char	*lineprint;
	
	fd = open("test.txt", O_RDONLY);
	lineprint = get_next_line(fd);
	printf("\n%s\n", lineprint);
	// printf("%s", get_next_line(fd));
	close(fd);
	return (0);
} */
