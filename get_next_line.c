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
char	*get_next_line(int fd)
{
	static char	*save_line;;
	char		*line;
	int			bytes_read;

	line = malloc(1);
	bytes_read = 1;
	while ((save_line == (char *)'\n') && (bytes_read != 0))
	{
		// read from fd
		bytes_read = read(fd, line, 1);
		ft_strjoin(save_line, line);
		// if read fails, return NULL
		if (bytes_read == -1)
			return (NULL);
		// if read returns 0, return NULL
		if (bytes_read == 0)
			return (NULL);
		// if read returns > 0, return line
		if (bytes_read > 0)
			return (line);
	}
	// get_next_line(fd);
	return (line);
}
