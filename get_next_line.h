/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:18 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/12 20:58:15 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include <sys/types.h>
# include <sys/uio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

char		*get_next_line(int fd);
int			search_nl(char *s);
char		*new_buffer(char *buffer);
void		*free_buf(char **buffer, int returnval);
char		*copy_stash_buffer(char *buffer, char *stash);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
// char		*read_line(char *buffer, char *stash, int fd);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*current_line(char *buffer);
// void		*ft_calloc(size_t items, size_t size);
// size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *s);
#endif