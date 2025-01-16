# Project Name
NAME = minishell

# Directories
OBJ_DIR = ./object/
SRC_DIR = ./
LIBFT_DIR = ./libft/
SRC_FILE = $(wildcard $(SRC_DIR)*.c)

# Compiler and Flags
CC = cc
INCLUDE = -I$(SRC_DIR) -I$(LIBFT_DIR)
CFLAGS = -Wall -Wextra -Werror $(INCLUDE) #$(FSANITIZE)
FSANITIZE = -fsanitize=address -g
LIBFT = $(LIBFT_DIR)libft.a

# Targets
all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(NAME): $(OBJ_DIR) $(SRC_FILE) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC_FILE) $(LIBFT) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(OBJ_DIR):
	@[ -d $(OBJ_DIR) ] || (echo "Creating directory $(OBJ_DIR)" && mkdir -p $(OBJ_DIR))

clean:
	${RM} -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	${RM} $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "All files cleaned."

re: fclean all

.PHONY: all clean fclean re

