/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:30 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/15 11:50:00 by jschwabe         ###   ########.fr       */
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

// static char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*copy;
// 	char	*p;

// 	copy = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!copy || !s1 || !s2)
// 		return (NULL);
// 	p = copy;
// 	while (*s1)
// 		*p++ = *s1++;
// 	while (*s2)
// 		*p++ = *s2++;
// 	*p = '\0';
// 	return (copy);
// }

/*
** @brief free buffer and return value
** 
** @param buffer buffer to free
** @param stash content to return
** @return char* duplicate of stash
*/
char	*copy_stash_buffer(char *s1, char *s2)
{
	char	*copy;
	size_t	i;
	size_t	x;

	if (!s1 && s2)
		return (ft_strdup(s2));
	i = -1;
	x = 0;
	if (!s1)
		s1 = ft_strdup("");
	copy = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!copy)
		return (free(s1), NULL);
	while (s1[++i] != '\0')
		copy[i] = s1[i];
	while (s2[x] != '\0')
		copy[i++] = s2[x++];
	copy[i] = '\0';
	return (free_buf(&s1, 0), copy);
}

/* char	*copy_stash_buffer(char *s1, char *s2)
{
	char	*copy;
	size_t	i;
	size_t	x;

	if (!s1 && s2)
		return (ft_strdup(s2));
	i = -1;
	x = 0;
	if (!s1)
		s1 = ft_strdup("");
	copy = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!copy)
		return (free(s1), NULL);
	while (s1[++i] != '\0')
		copy[i] = s1[i];
	while (s2[x] != '\0')
		copy[i++] = s2[x++];
	copy[i] = '\0';
	return (free_buf(&s1), copy);
} */

/*
** @brief return a substring from a string
** 
** @param s string to substring
** @param start index to start substring
** @param len length of substring
** @return char* substring from string
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;
	size_t	i;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	substr = (char *) malloc(len + 1);
	if (!substr)
		return (0);
	i = 0;
	while (start < slen && i < len)
	{
		substr[i] = s[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
