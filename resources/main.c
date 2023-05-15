/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:38:53 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/15 17:59:55 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>

/* #include "get_next_line.h"

int	main(void)
{
	int fd;
	char *lineprint;

	fd = open("test.txt", O_RDONLY);
	while (lineprint)
	{
		lineprint = get_next_line(fd);
		if (lineprint == NULL)
			break ;
		printf("%s", lineprint);
	}
	close(fd);
	free(lineprint);
	return (0);
} */