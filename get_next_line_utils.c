/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/06/01 20:30:28 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*mallonize(char **line, size_t size)
{
	*line = malloc(size * sizeof(char));
	if (!*line)
		return (NULL);
	str_bzero(*line, size - 1);
	return (*line);
}

char	*check_n_free(char *line, int i)
{
	char	*tmp;

	if (!line)
		return (NULL);
	while (line[i] != 0)
	{
		i++;
	}
	if (!mallonize(&tmp, i + 1))
		return (free(line), NULL);
	i = -1;
	while (line[++i] != 0)
	{
		tmp[i] = line[i];
	}
	free(line);
	return (tmp);
}

char	*str_bzero(char *s, int n)
{
	int	i;

	i = 0;
	while (i <= n)
		s[i++] = 0;
	return (s);
}

int	eol(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

/*
** @brief copy content into start of buffer
** implements parts of substr funcionality for copying buffer
** @param buffer to replace
** @return new buffer, NULL on failure
*/
void	clean_buffer(char *buffer)
{
	int	i;
	int	nl;

	nl = eol(buffer);
	i = 0;
	if (buffer[nl] != '\n')
		buffer[i++] = 0;
	else
		nl += 1;
	i -= 1;
	while (++i < BUFFER_SIZE - nl)
		buffer[i] = buffer[nl + i];
	buffer[i] = '\0';
}
