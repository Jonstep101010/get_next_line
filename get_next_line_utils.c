/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/10 19:29:36 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_calloc(size_t items, size_t size)
{
	void			*ptr;
	size_t			n;
	size_t			i;
	unsigned char	*cast;

	n = items * size;
	if (items && (n) / items != size)
		return (0);
	ptr = malloc(n);
	if (!ptr)
		return (0);
	cast = ptr;
	i = 0;
	while (i < n)
	{
		cast[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;

	if (str == NULL)
		return (NULL);
	ptr = (char *)str;
	if (*ptr == (char)c)
		return (ptr);
	while (*ptr++)
		if (*ptr == (char)c)
			return (ptr);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*copy;
	size_t	i;
	size_t	x;

	i = -1;
	x = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (free(s1), NULL);
		s1[0] = '\0';
	}
	// if (!s2)
	// 	return (s1);
	copy = (char *) ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!copy)
		return (free(s1), NULL);
	while (s1[++i] != '\0')
		copy[i] = s1[i];
	while (s2[x] != '\0')
		copy[i++] = s2[x++];
	copy[i] = '\0';
	return (free(s1), copy);
}

//strjoin needs to work if string does not exist
//free string