#name project minishell
NAME = minishell

#Directories
OBJ_DIR = ./object/
SRC_DIR = ./
SRC_FILE = ${wildcard *.c}

#COMPILER FLAGS
CC = cc
INCLUDE = -I$(SRC_DIR) -lreadline
CFLAGS = -Wall -Wextra -Werror $(INCLUDE) $(FSANITIZE)
FSANITIZE = -fsanitize=address -g

#TARGET
all : $(OBJ_DIR) $(NAME)

$(NAME) : $(SRC_FILE)
	$(CC) $(CFLAGS) -o $(NAME) $(INCLUDE) 
$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $>

$(OBJ_DIR) :
	@[ -d ${OBJ_DIR} ] || (echo "Creating directory ${OBJ_DIR}" && mkdir -p ${OBJ_DIR})

clean :
	${RM} ${OBJ_DIR}

fclean : clean
		${RM} ${NAME}
		@echo

re : fclean all

.PHONY: all clean fclean re