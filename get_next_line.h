/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:18 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/18 23:24:44 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

char		*get_next_line(int fd);
char		*read_line(char *buf, int fd, int *counter, char **line);
void		clean_buffer(char *buffer);
char		*check_n_free(char *line);
char		*callocate(char **line, int *count, char *buffer, int marker);
char		*ft_bzero(char *s, int n);
int			eol(char *s);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
#endif