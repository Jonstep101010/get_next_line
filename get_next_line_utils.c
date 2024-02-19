/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2024/02/19 22:41:45 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef LIBFT_H

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*d;
	const char		*s = src;

	d = dst;
	if (!d && !s)
		return (0);
	while (n-- && (d || s))
		*d++ = *s++;
	return (dst);
}

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = str;
	i = 0;
	while (i < n)
		ptr[i++] = c;
	return (str);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	if (nitems && (nitems * size) / nitems != size)
		return (0);
	ptr = malloc(nitems * size);
	if (!ptr)
		return (0);
	return ((ft_memset(ptr, 0, nitems * size)));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	x;

	srclen = 0;
	while (src[srclen] != '\0')
		++srclen;
	if (!size)
		return (srclen);
	x = -1;
	while ((src[++x] != '\0') && (x < size - 1))
	{
		dst[x] = src[x];
	}
	if (!src[x] || (x == size - 1))
		dst[x] = 0;
	return (srclen);
}
#endif // LIBFT_H

int	index_of(char *str, char c, int max_len)
{
	int	i;

	i = 0;
	while (i < max_len && str[i] != c && str[i] != '\0')
		i++;
	return (i);
}
