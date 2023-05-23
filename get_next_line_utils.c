/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/23 17:29:11 by jschwabe         ###   ########.fr       */
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
** @brief copy content into new buffer, free old using free_buf
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
	while (buffer[nl] != '\n' && i < BUFFER_SIZE)
		buffer[i++] = 0;
	if (buffer[nl] == '\n')
		nl += 1;
	while (i < BUFFER_SIZE - nl)
	{
		buffer[i] = buffer[nl + i];
		i++;
	}
	buffer[i] = 0;
}
