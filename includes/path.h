#ifndef PATH_H
# define PATH_H

# define NODE_VALUE					100

# define START_CHAR					'2'
# define END_CHAR					'3'

# define WALKABLE_CHAR				'0'
# define WALL_CHAR					'1'
# define TESTED_CHAR				'3'
# define WAY_CHAR					'5'

# define START_DISPLAY_CHAR			"\033[07m "
# define END_DISPLAY_CHAR			"\033[07m "
# define WALKABLE_DISPLAY_CHAR		"\033[07m "
# define WALL_DISPLAY_CHAR			"\033[07m "
# define TESTED_DISPLAY_CHAR		"\033[07m "
# define WAY_DISPLAY_CHAR			"\033[07m "

#define START						"\033["
#define END							"m"
#define WHITE						"0"
#define RED							"31"
#define GREEN						"32"
#define YELLOW						"33"
#define BLUE						"34"
#define CYAN						"36"
#define MANGETA						"35"

# include <libft.h>

typedef struct				s_node
{
	char					*name;
	int						x;
	int						y;
	int						f_score; //Weight
	int						g_score; //dist since start to current
	int						h_score; //flying dist since current and end node
	struct s_node			*parent;
	char					walkable;
	char					way;
}							t_node;

typedef struct				s_path
{
	t_node					*start;
	t_node					*end;
	t_node					***map;
	int						map_x;
	int						map_y;
	t_List					*map_raw;
	t_List					*open_lst;
	t_List					*close_lst;
	char					check_diag;
}							t_path;

t_node						*create_node(char *name, int x, int y);
t_path						*get_map(const char *const filename);
t_List						*astar(t_path *path, char check_diag);

#endif
