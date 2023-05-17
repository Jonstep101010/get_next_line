/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/17 19:39:17 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*setnull(char *s)
{
	free(s);
	s = NULL;
	return (NULL);
}

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

void	clean_buffer(char *buffer)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (buffer[check_eol(buffer)] != '\n' && i < BUFFER_SIZE)
		buffer[i++] = '\0';
	if (buffer[check_eol(buffer)] == '\n')
		start = check_eol(buffer) + 1;
	while (i < BUFFER_SIZE)
	{
		if (start + i <= BUFFER_SIZE)
			buffer[i] = buffer[start + i];
		i++;
	}
	buffer[BUFFER_SIZE] = 0;
}

int	check_eol(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_bzero(char *s, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}
