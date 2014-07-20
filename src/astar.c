#include <path.h>
#include <libft.h>

#include <stdio.h>
#include <stdlib.h>

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

int				in_list(t_List *lst, const char *const name)
{
	t_node			*node;

	while (lst != NULL)
	{
		node = lst->content;
		if (ft_strcmp(node->name, name) == 0)
			return (1);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (0);
}

int					max(const int a, const int b)
{
	if (a < b)
		return (b);
	return (a);
}

int					heuristic(t_node *const current, t_node *const end)
{
	int				dx;
	int				dy;

	dx = abs(current->x - end->x);
	dy = abs(current->y - end->y);
	return (NODE_VALUE * max(dx, dy));
}

void				calculate_current(t_data *data, t_node *current, t_node *parent)
{
	current->parent = parent;
	current->g_score = parent->g_score + NODE_VALUE;
	current->h_score = heuristic(current, data->end);
	current->f_score = current->h_score + current->g_score;

}

void				astar_check(t_data *const data,
						t_node *const parent, const int x, const int y)
{
	t_node			*current = data->map[y][x];
	int				tmp;

	current->way = TESTED_CHAR;
	if (current->walkable == WALL_CHAR || in_list(data->close_lst, current->name))
		return ;
	if (!in_list(data->open_lst, current->name))
	{
		ft_lstadd_back(&data->open_lst, ft_lstnew(current, sizeof(t_node *)));
		current->parent = parent;
		current->g_score = parent->g_score + NODE_VALUE;
		current->h_score = heuristic(current, data->end);
		current->f_score = current->h_score + current->g_score;
	}
	else
	{
		tmp = parent->g_score + NODE_VALUE;
		if (tmp < current->g_score)
		{
			current->parent = parent;
			current->g_score = tmp;
			current->h_score = heuristic(current, data->end);
			current->f_score = current->h_score + current->g_score;
		}
	}
}

void				check_neighbours(t_data *const data, t_node *const current)
{
	if (current->x - 1 >= 0)
		astar_check(data, current, current->x - 1, current->y);
	if (current->x + 1 < data->map_x)
		astar_check(data, current, current->x + 1, current->y);
	if (current->y + 1 < data->map_y)
		astar_check(data, current, current->x, current->y + 1);
	if (current->y - 1 >= 0)
		astar_check(data, current, current->x, current->y - 1);

	if (current->x - 1 >= 0 && current->y - 1 >= 0)
		astar_check(data, current, current->x - 1, current->y - 1);
	if (current->x + 1 < data->map_x && current->y - 1 >= 0)
		astar_check(data, current, current->x + 1, current->y - 1);
	if (current->x - 1 >= 0 && current->y + 1 < data->map_y)
		astar_check(data, current, current->x - 1, current->y + 1);
	if (current->x + 1 < data->map_x && current->y + 1 < data->map_y)
		astar_check(data, current, current->x + 1, current->y + 1);
}

int					remove_comp(void *a, void *b)
{
	t_node			*node_a;
	t_node			*node_b;

	node_a = (t_node *)a;
	node_b = (t_node *)b;
	if (ft_strcmp(node_a->name, node_b->name) == 0)
		return (0);
	return (-1);
}

t_node				*astar(t_data *const data)
{
	t_node			*current;
	int				(*comp_function)(void *, void *);

	comp_function = remove_comp;
	data->open_lst = NULL;
	data->close_lst = NULL;
	ft_lstadd_back(&data->open_lst, ft_lstnew(data->start, sizeof(t_node *)));
	while (data->open_lst != NULL)
	{
		current = get_smallest_f_score(data->open_lst);
		data->open_lst = ft_lst_remove(data->open_lst, comp_function, current);
		ft_lstadd_back(&data->close_lst, ft_lstnew(current, sizeof(t_node *)));
		check_neighbours(data, current);
		if (in_list(data->close_lst, data->end->name))
			return (current);
	}
	return (NULL);
}
