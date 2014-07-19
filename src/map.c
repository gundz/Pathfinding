/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/19 17:19:44 by fgundlac          #+#    #+#             */
/*   Updated: 2014/07/19 23:45:19 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <path.h>

#include <libft.h>

#include <fcntl.h>
#include <stdio.h>

t_List				*get_file(const char *const filename)
{
	const int		fd = open(filename, O_RDONLY);
	char			*buf;
	t_List			*map_raw;

	map_raw = NULL;
	if (fd == -1)
		return (NULL);
	while (get_next_line(fd, &buf) > 0)
		ft_lstadd_back(&map_raw, ft_lstnew(buf, ft_strlen(buf) + 1));
	return (map_raw);
}

int					check_map(t_data *const data)
{
	int				x_tmp = 0;
	t_List			*lstwalker;

	lstwalker = data->map_raw;
	if (lstwalker != NULL)
	{
		data->map_y++;
		data->map_x = ft_strlen((char *)lstwalker->content);
	}
	if (lstwalker->next != NULL)
		lstwalker = lstwalker->next;
	while (lstwalker != NULL)
	{
		data->map_y++;
		x_tmp = ft_strlen((char *)lstwalker->content);
		if (x_tmp != data->map_x)
			return (-1);
		if (lstwalker->next == NULL)
			break ;
		lstwalker = lstwalker->next;
	}
	return (0);
}

void				create_map(t_data *const data)
{
	t_node			***map;
	int				i;
	int				j;
	int				k;

	if (!(map = (t_node ***)malloc(sizeof(t_node **) * data->map_y)))
		return ;
	i = 0;
	k = 0;
	while (i < data->map_y)
	{
		if (!(map[i] = (t_node **)malloc(sizeof(t_node *) * data->map_x)))
			return ;
		j = 0;
		while (j < data->map_x)
		{
			map[i][j] = create_node(ft_itoa(k), j, i);
			j++;
			k++;
		}
		i++;
	}
	data->map = map;
}

int					set_start_end_walk(t_data *const data,
		const char c, const int x, const int y)
{
	if (c == START_CHAR)
	{
		if (data->start != NULL)
			return (-1);
		data->start = data->map[y][x];
		data->map[y][x]->walkable = WALKABLE_CHAR;
	}
	else if (c == END_CHAR)
	{
		if (data->end != NULL)
			return (-1);
		data->end = data->map[y][x];
		data->map[y][x]->walkable = WALKABLE_CHAR;
	}
	else
		data->map[y][x]->walkable = c;
	return (0);
}

int					set_special(t_data *const data)
{
	t_List			*lstwalker;
	char			*tmp;
	int				x;
	int				y = 0;

	lstwalker = data->map_raw;
	while (lstwalker != NULL)
	{
		tmp = lstwalker->content;
		x = 0;
		while (tmp[x] != '\0')
		{
			if (set_start_end_walk(data, tmp[x], x, y) == -1)
				return (-1);
			x++;
		}
		y++;
		if (lstwalker->next == NULL)
			break ;
		lstwalker = lstwalker->next;
	}
	if (data->start == NULL || data->end == NULL)
		return (-1);
	return (0);
}

t_data				*get_map(const char *const filename)
{
	t_data			*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->start = NULL;
	data->end = NULL;
	data->map_raw = get_file(filename);
	if (check_map(data) != 0)
	{
		printf("Invalid map\nInvalid map integrity\n");
		return (NULL);
	}
	create_map(data);
	if (set_special(data) == -1)
	{
		printf("Invalid map\nNo start or end OR multiple start or end set\n");
		printf("EMPY CHAR = %c\nWALL CHAR = %c\n", WALKABLE_CHAR, WALL_CHAR);
		printf("START CHAR = %c\nEND CHAR = %c\n", START_CHAR, END_CHAR);
		return (NULL);
	}
	return (data);
}
