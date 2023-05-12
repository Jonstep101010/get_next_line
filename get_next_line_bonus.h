/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:12:46 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/13 01:28:23 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include <sys/types.h>
# include <sys/uio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char		*get_next_line(int fd);
char		*replace_buffer(char *buffer);
void		*free_buf(char **buffer, int returnval);
char		*copy_stash_buffer(char *buffer, char *stash);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*parse_line(char *s);
char		*ft_strdup(const char *s);
#endif