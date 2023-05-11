/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jonas.paul.schwabe@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:38:53 by jschwabe          #+#    #+#             */
/*   Updated: 2023/05/11 12:40:39 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* int	main(int argc, char *argv[])
{
	char *line;
	int fd;
	int w_fd;
	const char *tests[] = {
		"test.txt"};
	const int files = sizeof(tests) / sizeof(tests[0]);

	if (argc > 2)
		return (-1);
	if (argc > 1)
	{
		if (fd < 0)
		{
			perror("r1");
			exit(1);
		}
		read_f(fd);
		w_fd = write(fd, "\nhello\n", ft_strlen("\nhello\n"));
		// printf("wd = %d\n", w_fd);
		close(fd);
	}
} */

/* #include "get_next_line.h"

int	main(void)
{
	int	fd;
	char	*lineprint;

	fd = open("empty.txt", O_RDONLY);
	lineprint = get_next_line(fd);
	// printf("\n%s\n", lineprint);
	// printf("%s", get_next_line(fd));
	close(fd);
	free(lineprint);
	return (0);
} */