NAME		:=	cub3d

LIBS		:=	./lib/libft.a
MLX			?=	./MLX42
MLXLIB		:= $(MLX)/build/libmlx42.a
HEADER		:=	-Ilibft -Iinc -I$(MLX)/include/MLX42

HEADERS		:=	inc/libft.h inc/cub3d.h include/struct.h $(MLX)/include/MLX42/MLX42.h
OBJ_DIR		:=	obj
SRC_DIR 	:=	src

CC := cc
CFLAGS := -Wall -Wextra -Werror

SOURCES := 	vector.c render.c \
			main.c scanner.c \
			scanner_utils.c \
			parser.c parser_utils.c \
			matrix_utils.c \
			init.c flood_fill.c\
			draw.c game_loop_utils.c \
			game_loop.c init.c \
			matrix_utils.c \
			render.c render_utils.c \
			end.c

OBJECTS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES))
SOURCES := $(addprefix $(SRC_DIR)/,$(SOURCES))


ifeq ($(shell uname -s),Darwin)			# Mac
	MLXLIB += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(shell uname -s),Linux)		# Linux
	MLXLIB += -lglfw -ldl -pthread -lm
endif




GREEN = \x1b[32;01m
RED = \x1b[31;01m
YELLOW = \033[33;1m
BOLD = \033[1m
RESET = \x1b[0m
RM = /bin/rm -f

all: $(NAME) 

$(NAME): $(OBJECTS) $(LIBS)
	@$(CC) $^ $(LIBS) $(MLXLIB) $(CFLAGS) -o $(NAME)
	@printf "$(GREEN) $(BOLD)======= Created program $(NAME) ======= $(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
	@printf "$(YELLOW) $(BOLD)Compiling... $(RESET) $(notdir $<)\n"

$(MLXLIB):
	@cmake MLX42 -B MLX42/build
	@make -C MLX42/build -j4

clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(RED) $(BOLD) Deleting objects... $(RESET)\n"

fclean: clean
	@$(RM) -rf $(NAME)
	@printf "$(RED) $(BOLD) Deleting $(NAME)... $(RESET)\n"

re: fclean all

.PHONY: all clean fclean re