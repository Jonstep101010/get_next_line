/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:31:07 by jschwabe          #+#    #+#             */
/*   Updated: 2023/04/13 20:35:48 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strcat;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	strcat = malloc(s1_len + s2_len + 1);
	if (strcat == 0)
		return (0);
	ft_strlcpy(strcat, s1, s1_len + 1);
	ft_strlcat(strcat, s2, s1_len + s2_len + 1);
	return (strcat);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	x;

	x = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	while ((src[x] != '\0') && (x < size - 1))
	{
		dst[x] = src[x];
		x++;
	}
	if ((src[x] == '\0') || (x == size - 1))
		dst[x] = '\0';
	return (srclen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;
	size_t	dstlen;

	i = 0;
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	while ((i < srclen) && (i + dstlen < dstsize - 1))
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	dst[i + dstlen] = '\0';
	return (dstlen + srclen);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	size;

	size = ft_strlen(s) + 1;
	copy = malloc(size);
	if (!copy)
		return (0);
	ft_memcpy(copy, s, size);
	return (copy);
}

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;

	ptr = (char *) str;
	if (*ptr == (char) c)
		return (ptr);
	while (*ptr++)
		if (*ptr == (char) c)
			return (ptr);
	return (0);
}

static char	*helper_copy_terminate(char *substr, char const *s, unsigned int start, size_t len)
{
	ft_strlcpy(substr, s + start, len);
	ft_strlcat(substr, "", len);
	return (substr);
}

/*
** @brief return substring for string - allocate memory
** @param s string from which to create substring
** @param start start index of substring in s
** @param len maximum length of substring
** @return substring, NULL if allocation fails
** @details check if string is empty, set length of string
** \details guard against index start being greater than length -
** \details return "" (size 1); check len against size - index (substr)
** \details if so: set len to them; allocate with malloc(len+1)
** \details check for empty substr; set to values in string for <len
** \details terminate & return
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	substr = (char *) malloc(len + 1);
	if (substr)
		return(helper_copy_terminate(substr, s, start, len + 1));
	return (0);
}

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
