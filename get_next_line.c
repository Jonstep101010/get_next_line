/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:25:50 by jschwabe          #+#    #+#             */
/*   Updated: 2023/12/21 11:02:25 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Function: check_free
** ---------------------
** Checks if the line pointer is not NULL and frees the memory allocated to it.
** Then, it allocates a new memory block of the same size as the line and copies
** the contents of the line to the new memory block. Finally, it frees the old
** memory block and returns the new memory block.
**
** line: The line pointer to be checked and freed.
**
** returns: The new memory block with the contents of the line, or NULL if an
**          error occurred during memory allocation.
*/
static char	*check_free(char *line)
{
	char	*tmp;
	int		i;

	if (!line)
		return (NULL);
	for (i = 0; line[i] != '\0'; ++i)
		;
	tmp = (char *) ft_calloc(sizeof(char), i + 1);
	if (!tmp)
		return (free(line), NULL);
	for (i = 0; line[i] != '\0'; ++i)
		tmp[i] = line[i];
	free(line);
	return (tmp);
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

/*
** Function: check_buffer
** ----------------------
** Checks the buffer for a newline character. If found, it allocates a new line
** buffer and copies the contents of the buffer up to the newline character to
** the line buffer. Then, it cleans the buffer. If a newline character is not
** found, it reads from the file descriptor and appends the contents to the line
** buffer. Finally, it checks and frees the line buffer.
**
** fd: The file descriptor to read from.
** line: The pointer to the line buffer.
**
** returns: The new line buffer with the contents read from the file descriptor,
**          or NULL if an error occurred during memory allocation.
*/
char	*get_next_line(int fd)
{
	char	*line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	/* check_buffer */
	static char		buf[BUFFER_SIZE + 1];
	int				counter = 0;

	while (counter <= BUFFER_SIZE && buf[counter])
	{
		if (buf[counter] == '\n')
		{
			line = (char *) ft_calloc(sizeof(char), BUFFER_SIZE + 1);
			if (!line)
				return (NULL);
			ft_memcpy(line, buf, counter + 1);// copy buffer into line
			clean_buffer(buf);// move stuff after newline to beginning of buffer
			return (check_free(line));
		}
		counter++;
	}
	if (buf[counter] != '\n')
		read_line(buf, fd, &counter, &line);
	return (check_free(line));
}

/*
** Function: clean_buffer
** ----------------------
** Cleans the buffer by shifting the contents after the newline character to the
** beginning of the buffer.
**
** buf: The buffer to be cleaned.
*/
void	clean_buffer(char *buf)
{
	int	nl_index = 0;

	while (buf[nl_index] && buf[nl_index] != '\n')
		nl_index++;
	buf[nl_index] != '\n' ? buf[nl_index++] = 0 : nl_index++;
	ft_memcpy(buf, (const void *)(buf + nl_index), (BUFFER_SIZE - nl_index) + 1);
}
