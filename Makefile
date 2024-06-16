SHELL :=  /bin/bash

NAME := cub3d
SRC_DIR := src
OBJ_DIR := obj
LIBFT := -L. lib/libft.a
HEADERS := -I ./inc
INC := inc
SOURCES := 	$(SRC_DIR)/main.c $(SRC_DIR)/scanner.c $(SRC_DIR)/utils.c $(SRC_DIR)/color_utils.c  \
			$(SRC_DIR)/scanner_utils.c $(SRC_DIR)/scanner_utils2.c
MLX42 = lib/libmlx42.a  -Iinclude -ldl -lglfw -pthread -lm


OBJECTS := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
CC := cc
CFLAGS := -I $(INC) -Wall -Wextra -Werror -g


GREEN = \x1b[32;01m
RED = \x1b[31;01m
YELLOW = \033[33;1m
BOLD = \033[1m
RESET = \x1b[0m
RM = /bin/rm -f

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJECTS) $(SOURCES)
	@$(CC) $(CFLAGS) $(SOURCES) $(LIBFT) $(MLX42) -o $(NAME)
	@printf "$(GREEN) $(BOLD)======= Created program $(NAME) ======= $(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(HEADERS) $< -o $@
	@printf "$(YELLOW) $(BOLD)Compiling... $(RESET) $(notdir $<)\n"

clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(RED) $(BOLD) Deleting objects... $(RESET)\n"

fclean: clean
	@$(RM) -rf $(NAME)
	@printf "$(RED) $(BOLD) Deleting $(NAME)... $(RESET)\n"

re: fclean all

.PHONY: all clean fclean re