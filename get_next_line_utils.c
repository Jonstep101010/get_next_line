/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/05 16:35:35 by jschwabe         ###   ########.fr       */
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

	ptr = (char *)str;
	if (*ptr == (char)c)
		return (ptr);
	while (*ptr++)
		if (*ptr == (char)c)
			return (ptr);
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*copy;
	size_t	s1len;
	size_t	s2len;
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	copy = (char *) malloc(s1len + s2len + 1);
	if (!copy)
		return (0);
	if (!s1 && !s2)
		copy[i] = '\0';
	while (i < s1len + s2len && i < s1len)
	{
		copy[i] = s1[i];
		i++;
	}
	while (i < s1len + s2len)
		copy[i] = s2[x];
	copy[i] = '\0';
	return (copy);
}
