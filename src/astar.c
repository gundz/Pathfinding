#include <path.h>
#include <libft.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int					node_comp(void *a, void *b)
{
	t_node			*node_a;
	t_node			*node_b;

	node_a = (t_node *)a;
	node_b = (t_node *)b;
	if (ft_strcmp(node_a->name, node_b->name) == 0)
		return (0);
	return (-1);
}

t_node				*get_smallest_f_score(t_List *const list)
{
	t_List			*lstwalker;
	t_node			*tmp;
	t_node			*ret;

	lstwalker = list;
	ret = NULL;
	tmp = NULL;
	while (lstwalker != NULL)
	{
		if (ret == NULL)
			ret = lstwalker->content;
		tmp = lstwalker->content;
		if (tmp->f_score < ret->f_score)
			ret = tmp;
		if (lstwalker->next == NULL)
			break ;
		lstwalker = lstwalker->next;
	}
	return (ret);
}

int					heuristic(t_node *const current,
						t_node *const end)
{
	const int		dx = abs(current->x - end->x);
	const int		dy = abs(current->y - end->y);

	return (dx * dx + dy * dy);
}

void				calculate_current(t_data *const data, t_node *const current,
						t_node *const parent, const int g_score)
{
	current->parent = parent;
	current->g_score = g_score;
	current->h_score = heuristic(current, data->end) * NODE_VALUE;
	current->f_score = current->h_score + current->g_score;
}

void				astar_check(t_data *const data,
						t_node *const parent, const int x, const int y)
{
	t_node			*current = data->map[y][x];
	int				tmp;
	int				(*comp_func)(void *, void *);

	comp_func = node_comp;
	current->way = TESTED_CHAR;
	if (current->walkable == WALL_CHAR ||
			ft_in_lst(data->close_lst, comp_func, current))
		return ;
	if (!ft_in_lst(data->open_lst, comp_func, current))
	{
		ft_lstadd_back(&data->open_lst, ft_lstnew(current, sizeof(t_node *)));
		calculate_current(data, current, parent, parent->g_score + NODE_VALUE);
	}
	else
	{
		tmp = parent->g_score + NODE_VALUE;
		if (tmp < current->g_score)
			calculate_current(data, current, parent, tmp);
	}
}

void				check_neighbours(t_data *const data, t_node *const current)
{
	if (current->x - 1 >= 0)
		astar_check(data, current, current->x - 1, current->y);
	if (current->y + 1 < data->map_y)
		astar_check(data, current, current->x, current->y + 1);
	if (current->x + 1 < data->map_x)
		astar_check(data, current, current->x + 1, current->y);
	if (current->y - 1 >= 0)
		astar_check(data, current, current->x, current->y - 1);

	if (data->check_diag == 1)
	{
		if (current->x - 1 >= 0 && current->y - 1 >= 0)
			astar_check(data, current, current->x - 1, current->y - 1);
		if (current->x + 1 < data->map_x && current->y - 1 >= 0)
			astar_check(data, current, current->x + 1, current->y - 1);
		if (current->x - 1 >= 0 && current->y + 1 < data->map_y)
			astar_check(data, current, current->x - 1, current->y + 1);
		if (current->x + 1 < data->map_x && current->y + 1 < data->map_y)
			astar_check(data, current, current->x + 1, current->y + 1);
	}
}

t_List				*invert_list(t_node *node)
{
	t_List			*new;

	new = NULL;
	while (node != NULL)
	{
		ft_lstadd_front(&new, ft_lstnew(node, sizeof(t_node *)));
		if (node->parent == NULL)
			break ;
		node = node->parent;
	}
	return (new);
}

t_List				*astar(t_data *const data, char check_diag)
{
	t_node			*current;
	int				(*comp_function)(void *, void *);

	comp_function = node_comp;
	data->open_lst = NULL;
	data->close_lst = NULL;
	data->check_diag = check_diag;
	ft_lstadd_back(&data->open_lst, ft_lstnew(data->start, sizeof(t_node *)));
	while (data->open_lst != NULL)
	{
		current = get_smallest_f_score(data->open_lst);
		data->open_lst = ft_lst_remove(data->open_lst, comp_function, current);
		ft_lstadd_back(&data->close_lst, ft_lstnew(current, sizeof(t_node *)));
		check_neighbours(data, current);
		if (ft_in_lst(data->close_lst, comp_function, data->end))
			return (invert_list(current));
	}
	return (NULL);
}
