/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/19 16:53:51 by fgundlac          #+#    #+#             */
/*   Updated: 2014/07/20 20:29:59 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void			gen_map(int x, int y, int start_x, int start_y,
					int end_x, int end_y, char *filename)
{
	int			fd;
	int			i = 0;
	int			j = 0;

	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (j == start_x && i == start_y)
				write(fd, "2", 1);
			else if (j == end_x && i == end_y)
				write(fd, "3", 1);
			else
				write(fd, "0", 1);
			j++;
		}
		i++;
		write(fd, "\n", 1);
	}
}

int				main(int argc, char **argv)
{
	if (argc == 8)
	{
		gen_map(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]),
				atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), argv[7]);
		return (-1);
	}
	else
		printf("Usage : X Y START_X START_Y END_X END_Y filename\n");
	return (0);
}
