SHELL :=  /bin/bash

NAME := cub3d
SRC_DIR := src
OBJ_DIR := obj
LIBFT := -L. lib/libft/libft.a
HEAD := inc/cub3d.h
INC := inc
SOURCES := 	$(SRC_DIR)/main.c
MLX42 = lib/MLX42/build/libmlx42.a
MLXFLAGS = lib/MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

OBJECTS := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
CC := cc
CFLAGS := -I $(INC) -Wall -Wextra -Werror


GREEN = \x1b[32;01m
RED = \x1b[31;01m
YELLOW = \033[33;1m
BOLD = \033[1m
RESET = \x1b[0m
RM = /bin/rm -f

all: $(NAME)

$(NAME): $(HEAD) $(OBJ_DIR) $(OBJECTS) $(SOURCES)
	@$(CC) $(CFLAGS) $(SOURCES) $(LIBFT) -o $(NAME)
	@printf "$(GREEN) $(BOLD)======= Created program $(NAME) ======= $(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(LIBFT) $< -o $@
	@printf "$(YELLOW) $(BOLD)Compiling... $(RESET) $(notdir $<)\n"

clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(RED) $(BOLD) Deleting objects... $(RESET)\n"

fclean: clean
	@$(RM) -rf $(NAME)
	@printf "$(RED) $(BOLD) Deleting $(NAME)... $(RESET)\n"

re: fclean all

.PHONY: all clean fclean re