NAME = libesdl.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

CFLAGS += `SDL2/SDL2/bin/sdl2-config --cflags`
LFLAGS += `SDL2/SDL2/bin/sdl2-config --libs`

PATH_INC = includes
PATH_OBJ = obj
PATH_SRC = src

SRC =	sdl_init.c \
	sdl_events.c \
	sdl_fps_counter.c \
	sdl_draw.c \

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all : SDL2 $(NAME)

$(NAME) : namemes $(OBJ)
	@ ar -rc $@ $(OBJ)
	@ ranlib $(NAME)
	@ echo " \033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
	@ echo -n .
	@ mkdir -p $(PATH_OBJ)
	@ $(CC) $(CFLAGS) -o $@ -c $^ -I $(PATH_INC)

clean :
	@ rm -rf $(PATH_OBJ)
	@ make clean -C SDL2/
	@ echo "Cleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

fclean : clean
	@ rm -f $(NAME)
	@ make fclean -C SDL2/
	@ echo "Fcleaning $(NAME) \
		\033[4m\033[95md\033[93mo\033[32mn\033[96me \033[91m!\033[0m"

re : fclean all

namemes :
	@ echo -n Compiling $(NAME)

SDL2:
	@ make -C SDL2/

.PHONY: SDL2 clean fclean re
