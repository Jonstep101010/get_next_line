/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/18 23:25:01 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_n_free(char *line)
{
	char	*tmp;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != 0)
		i++;
	tmp = malloc((i + 1) * sizeof(char));
	if (!tmp)
		return (free(line), line = NULL);
	ft_bzero(tmp, i);
	i = 0;
	while (line[i] != 0)
	{
		tmp[i] = line[i];
		i++;
	}
	free(line);
	line = NULL;
	return (tmp);
}

char	*ft_bzero(char *s, int n)
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
** @brief handle buffer freeing and return values
** 
** @param buffer address of buffer to free
** @param returnval 1 to also return buffer duplicate, 0 to free buffer
** @return char* if line return is expected\
** @return void* if free or buffer == NULL
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
