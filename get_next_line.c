/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:31:02 by jschwabe          #+#    #+#             */
/*   Updated: 2023/04/13 20:41:00 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** @brief read a line from a file descriptor
** @param fd file descriptor to read from
** @return line read from file descriptor
*/
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	*save_line = NULL;
	char		*line;
	int			bytes_read;

	if (save_line == NULL)
		save_line = malloc(1);
	line = malloc(1024); // allocate enough memory for a line
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, line, 1024);
		if (bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
		line[bytes_read] = '\0'; // terminate the string
		save_line = ft_strjoin(save_line, line);
		if (save_line == NULL)
		{
			free(line);
			return (NULL);
		}
		if (ft_strchr(save_line, '\n') != NULL)
			break;
	}
	free(line);
	if (bytes_read == 0 && save_line[0] == '\0')
		return (NULL);
	line = ft_substr(save_line, 0, ft_strlen(save_line) - ft_strlen(ft_strchr(save_line, '\n')));
	if (line == NULL)
		return (NULL);
	save_line = ft_strdup(ft_strchr(save_line, '\n') + 1);
	return (line);
}
