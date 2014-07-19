#include <libft.h>
#include <path.h>

t_node				*create_node(char *name, int x, int y)
{
	t_node			*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	node->name = name;
	node->x = x;
	node->y = y;
	node->f_score = 0;
	node->g_score = 0;
	node->h_score = 0;
	node->parent = NULL;
	node->way = '0';
	return (node);
}
