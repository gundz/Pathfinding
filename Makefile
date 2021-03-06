NAME = Pathfinding

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -O3

PATH_INC = includes/

PATH_SRC = src

PATH_OBJ = obj

SRC =		main.c \
			node.c \
			astar.c \
			map.c \
			show_shell.c \

LIB_PATH = libft/
LIB_INC = $(LIB_PATH)includes
LIB_NAME = libft.a

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all: lib $(NAME) map_gen

$(NAME): $(OBJ)
	@ $(CC) $(OBJ) $(CFLAGS) -I $(LIB_INC) -I $(PATH_INC) $(LIB_PATH)$(LIB_NAME) -o $(NAME)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c)
	@ mkdir -p $(PATH_OBJ)
	@ $(CC) -c $^ -I $(PATH_INC) -I $(LIB_INC) $(CFLAGS) -o $@

lib:
	@ make -C $(LIB_PATH)

map_gen:
	@ make -C map_gen/

clean:
	@ rm -rf $(PATH_OBJ)
	@ make clean -C $(LIB_PATH)

fclean: clean
	@ rm -rf $(NAME)
	@ make fclean -C $(LIB_PATH)

re: fclean all

.PHONY: clean fclean re
