/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:18 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/17 19:38:50 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

char		*get_next_line(int fd);
char		*read_line(char *buffer, int fd, int *count, char **line);
int			check_eol(char *buffer);

char		*check_n_free(char *line);

void		clean_buffer(char *buffer);
char		*callocate(char **line, int *count, char *buffer, int marker);
char		*ft_bzero(char *s, int size);
void		*setnull(char *s);
void		copy_line(int *count, char *stash, char **line);
#endif