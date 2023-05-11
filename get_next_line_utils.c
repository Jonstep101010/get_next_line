/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/11 18:20:55 by jschwabe         ###   ########.fr       */
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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i_src;
	size_t	i_dst;
	size_t	dstlen;

	i_src = 0;
	dstlen = ft_strlen(dst);
	i_dst = dstlen;
	if (dstsize <= dstlen || dstsize == 0)
		return (dstsize + ft_strlen(src));
	while (src[i_src] != '\0' && (i_src < dstsize - dstlen - 1))
	{
		dst[i_dst++] = src[i_src++];
	}
	dst[i_dst] = '\0';
	return (dstlen + ft_strlen(src));
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
		return (NULL);
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

	if (!str)
		return (NULL);
	ptr = (char *)str;
	c = (char) c;
	if (*ptr == c)
		return (ptr);
	while (*ptr++)
		if (*ptr == c)
			return (ptr);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*copy;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	copy = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!copy)
	{
		free(s1);
		return (NULL);
	}
	copy[0] = '\0';
	ft_strlcat(copy, s1, ft_strlen(s1) + 1);
	ft_strlcat(copy, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (free(s1), copy);
}

