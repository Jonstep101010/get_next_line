/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/11/16 14:31:07 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = str;
	i = 0;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (str);
}

char	*ft_calloc(char **line, size_t size)
{
	*line = malloc(size * sizeof(char));
	if (!*line)
		return (NULL);
	return (ft_memset(*line, 0, size));
}

/*
** @brief copy content into start of buffer
** implements parts of substr funcionality for copying buffer
** @param buffer to replace
** @return new buffer, NULL on failure
*/
void	clean_buffer(char *buffer)
{
	int	i = 0;
	int	nl = 0;

	while (buffer[nl] && buffer[nl] != '\n')
		++nl;
	if (buffer[nl] != '\n')
		buffer[i++] = 0;
	else
		nl += 1;
	i -= 1;
	while (++i < BUFFER_SIZE - nl)
		buffer[i] = buffer[nl + i];
	buffer[i] = '\0';
}
