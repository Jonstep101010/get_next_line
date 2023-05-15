/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/15 17:35:35 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** @brief handle buffer freeing and return values
** 
** @param buffer address of buffer to free
** @param returnval 1 to also return buffer duplicate, 0 to free buffer
** @return char* if line return is expected\
** @return void* if free or buffer == NULL
*/
void	*free_buf(char **buffer, int returnval)
{
	char	*line;

	if (!*buffer)
		return (NULL);
	if (returnval == 1)
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (line);
	}
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
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
}
