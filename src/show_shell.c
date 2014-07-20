#include <libft.h>
#include <path.h>

#include <stdio.h>

void			show_way(t_data *data)
{
	int			i = 0;
	int			j;

	while (i < data->map_y)
	{
		j = 0;
		while (j < data->map_x)
		{
			if (ft_strcmp(data->map[i][j]->name, data->start->name) == 0)
				printf(START CYAN END START_DISPLAY_CHAR START WHITE END);
			else if (ft_strcmp(data->map[i][j]->name, data->end->name) == 0)
				printf(START MANGETA END END_DISPLAY_CHAR START WHITE END);
			else if (data->map[i][j]->walkable == WALL_CHAR)
				printf(START RED END WALL_DISPLAY_CHAR START WHITE END);
			else if (data->map[i][j]->way == TESTED_CHAR)
				printf(START YELLOW END TESTED_DISPLAY_CHAR START WHITE END);
			else if (data->map[i][j]->way == WAY_CHAR)
				printf(START GREEN END WAY_DISPLAY_CHAR START WHITE END);
			else
				printf(WALKABLE_DISPLAY_CHAR);
			j++;
		}
		i++;
		printf("\n");
	}
}

void			set_way(t_node ***map, t_List *way)
{
	t_node		*tmp;

	tmp = NULL;
	while (way != NULL)
	{
		tmp = way->content;
		map[tmp->y][tmp->x]->way = WAY_CHAR;
		if (way->next == NULL)
			break ;
		way = way->next;
	}
}

void			show_shell(t_data *data, t_List *way)
{
	if (way == NULL)
	{
		printf("No valid way found !\n");
		return ;
	}
	set_way(data->map, way);
	show_way(data);
}
