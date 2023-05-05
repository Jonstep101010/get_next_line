/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:38:53 by jschwabe          #+#    #+#             */
/*   Updated: 2023/04/19 10:48:26 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char *argv[])
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
}