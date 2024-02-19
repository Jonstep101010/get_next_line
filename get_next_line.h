/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:26:18 by jschwabe          #+#    #+#             */
/*   Updated: 2024/02/19 22:48:41 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# ifdef LIBFT_H
#  include "libft.h"
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

/* -------------------------------------------------------------------------- */
/*                                    utils                                   */
/* -------------------------------------------------------------------------- */

int			index_of(char *str, char c, int max_len);

# ifndef LIBFT_H

void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *str, int c, size_t n);
void		*ft_calloc(size_t nitems, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
# endif

char		*get_next_line(int fd);

#endif
