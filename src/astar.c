#include <path.h>
#include <libft.h>

#include <stdio.h>
#include <stdlib.h>

#define NODE_VALUE 100

t_node				*get_smallest_f_score(t_List *list)
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

t_List				*remove_from_list(t_List *lst, char *name)
{
	t_node			*node;
	t_List			*tmp;
	t_List			*previous;

	if (lst == NULL)
		return (lst);
	previous = lst;
	node = previous->content;
	if (ft_strcmp(node->name, name) == 0)
	{
		lst = previous->next;
		return (lst);
	}
	tmp = previous->next;
	while (tmp != NULL)
	{
		node = tmp->content;
		if (ft_strcmp(node->name, name) == 0)
		{
			previous->next = tmp->next;
			return (lst);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (lst);
}

int				in_list(t_List *lst, char *name)
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

int					max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int					heuristic(t_node *current, t_node *end)
{
	int				dx;
	int				dy;

	dx = abs(current->x - end->x);
	dy = abs(current->y - end->y);
	return (NODE_VALUE * max(dx, dy));
}

void				astar_check(t_node *parent, t_node ***map, t_List **open, t_List **closed, t_node *end, int x, int y)
{
	t_node			*current;
	int				tmp;

	current = map[y][x];
	current->way = TESTED_CHAR;
	if (current->walkable == WALL_CHAR)
		return ;
	if (in_list(*closed, current->name))
		return ;
	if (!in_list(*open, current->name))
	{
		ft_lstadd_back(open, ft_lstnew(current, sizeof(t_node *)));
		current->parent = parent;
		current->g_score = parent->g_score + NODE_VALUE;
		current->h_score = heuristic(current, end);
		current->f_score = current->h_score + current->g_score;
	}
	else
	{
		tmp = parent->g_score + NODE_VALUE;
		if (tmp < current->g_score)
		{
			current->parent = parent;
			current->g_score = tmp;
			current->h_score = heuristic(current, end);
			current->f_score = current->h_score + current->g_score;
		}
	}
}

t_node				*astar(t_node ***map, t_node *start, t_node *end, int x, int y)
{
	t_List			*open_list = NULL;
	t_List			*closed_list = NULL;
	t_node			*current = NULL;

	ft_lstadd_back(&open_list, ft_lstnew(start, sizeof(t_node *)));
	while (open_list != NULL)
	{
		current = get_smallest_f_score(open_list);
		open_list = remove_from_list(open_list, current->name);
		ft_lstadd_back(&closed_list, ft_lstnew(current, sizeof(t_node *)));

		if (current->x - 1 >= 0)
			astar_check(current, map, &open_list, &closed_list, end, current->x - 1, current->y);
		if (current->x + 1 < x)
			astar_check(current, map, &open_list, &closed_list, end, current->x + 1, current->y);
		if (current->y + 1 < y)
			astar_check(current, map, &open_list, &closed_list, end, current->x, current->y + 1);
		if (current->y - 1 >= 0)
			astar_check(current, map, &open_list, &closed_list, end, current->x, current->y - 1);

		if (current->x - 1 >= 0 && current->y - 1 >= 0)
			astar_check(current, map, &open_list, &closed_list, end, current->x - 1, current->y - 1);
		if (current->x + 1 < x && current->y - 1 >= 0)
			astar_check(current, map, &open_list, &closed_list, end, current->x + 1, current->y - 1);
		if (current->x - 1 >= 0 && current->y + 1 < y)
			astar_check(current, map, &open_list, &closed_list, end, current->x - 1, current->y + 1);
		if (current->x + 1 < x && current->y + 1 < y)
			astar_check(current, map, &open_list, &closed_list, end, current->x + 1, current->y + 1);

		if (in_list(closed_list, end->name))
			return (current);
	}
	return (NULL);
}
