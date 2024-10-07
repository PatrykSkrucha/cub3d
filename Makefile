### VAR #######################################################
NAME		:=	cub3d

DEBUGGING	?=

LIBS		:=	./libft/libft.a
MLX			?=	./MLX42
MLXLIB		:= $(MLX)/build/libmlx42.a
HEADER		:=	-Ilibft -Iinclude -I$(MLX)/include/MLX42

HEADERS		:=	libft/libft.h include/cub3d.h include/struct.h $(MLX)/include/MLX42/MLX42.h
OBJ_DIR		:=	obj
SRC_DIR 	:=	src

### UTILS #####################################################
CFLAGS	:=	-Wall -Wextra -Werror -g -fsanitize=address
RM		:=	rm -rf

SRC 	:=	main.c \
			parser.c \
			map_utils.c \
			map_utils1.c \
			assets_parse.c	\
			elements_utils2.c\
			setup_map.c \
			setup_map_utils.c \
			init.c \
			utils.c \
			game_loop.c \
			game_controls.c \
			end.c \
			vector.c \
			raycast.c \
			draw.c \
			render_utils.c \
			render.c \
			parser_utils.c \
			parser_utils2.c

OBJ		:=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
SRC		:=	$(addprefix $(SRC_DIR)/,$(SRC))

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLXLIB += -lglfw -ldl -pthread -lm
else
	MLXLIB += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif


GREEN = \x1b[32;01m
RED = \x1b[31;01m
YELLOW = \033[33;1m
BOLD = \033[1m
RESET = \x1b[0m

RM = /bin/rm -rf


all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	@$(CC) $^ $(LIBS) $(MLXLIB) $(CFLAGS) -o $(NAME)
	@printf "$(GREEN) $(BOLD)======= Created program $(NAME) ======= $(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
	@printf "$(YELLOW) $(BOLD)Compiling... $(RESET) $(notdir $<)\n"

$(LIBS):
	make -C libft

mlx:
	@cmake MLX42 -B MLX42/build
	@make -C MLX42/build

clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(RED) $(BOLD) Deleting objects... $(RESET)\n"

fclean: clean
	@$(RM) -rf $(NAME)
	@printf "$(RED) $(BOLD) Deleting $(NAME)... $(RESET)\n"

deepclean: fclean
	@$(RM) $(MLX)/build

re: fclean all

.PHONY: clean all fclean re deepclean
