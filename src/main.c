#include <stdio.h>

#include <libft.h>
#include <path.h>

#include <SDL.h>

int				main(int argc, char **argv)
{
	t_data		*data;
	t_List		*way;

	if (argc != 3)
	{
		printf("Usage : map_file check_diag(0|1)\n");
		return (-1);
	}
	data = get_map(argv[1]);
	if (data == NULL)
		return (-1);
	way = astar(data, ft_atoi(argv[2]));
	return (0);
}
