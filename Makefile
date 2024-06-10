SHELL :=  /bin/bash

NAME := cub3d
SRC_DIR := src
OBJ_DIR := obj
#LIBFT_DIR := lib/Libft
LIBFT := ./inc/libft.a
HEAD := ./include/cub3d.h
SOURCES := 	$(SRC_DIR)/
#MLX42 = MLX42/build/libmlx42.a
#MLXFLAGS = MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))
CC := cc
CFLAGS := -Wall -Wextra -Werror
IFLAGS := -Iinclude -I$(LIBFT_DIR)/include


GREEN = \x1b[32;01m
RED = \x1b[31;01m
YELLOW = \033[33;1m
BOLD = \033[1m
RESET = \x1b[0m
RM = /bin/rm -f

all: $(NAME)

$(NAME): $(HEAD) $(OBJ_DIR) $(OBJECTS) $(SOURCES)
	@$(CC) $(CFLAGS) $(IFLAGS) $(SOURCES) $(LIBFT) $(LFLAGS) -o $(NAME)
	@printf "$(GREEN) $(BOLD)======= Created program $(NAME) ======= $(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(HEADERS) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(YELLOW) $(BOLD)Compiling... $(RESET) $(notdir $<)\n"

clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(RED) $(BOLD) Deleting objects... $(RESET)\n"

fclean: clean
	@$(RM) -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@printf "$(RED) $(BOLD) Deleting $(NAME)... $(RESET)\n"

re: fclean all

run:
	make && ./minishell

.PHONY: all clean fclean re