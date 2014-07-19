/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/19 16:53:51 by fgundlac          #+#    #+#             */
/*   Updated: 2014/07/19 18:42:33 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void			gen_map(int x, int y, char *filename)
{
	int			fd;
	int			i = 0;
	int			j = 0;

	fd = open(filename, O_WRONLY | O_CREAT);
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			write(fd, "0", 1);
			j++;
		}
		i++;
		write(fd, "\n", 1);
	}
}

int				main(int argc, char **argv)
{
	if (argc == 4)
	{
		gen_map(atoi(argv[1]), atoi(argv[2]), argv[3]);
		return (-1);
	}
	else
		printf("Usage : X Y filename\n");
	return (0);
}
