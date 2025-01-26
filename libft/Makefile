NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC =	 ft_atoi.c  ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c  ft_isprint.c 	ft_strlen.c	ft_strlcpy.c \
		ft_strlcat.c	ft_substr.c	ft_bzero.c ft_strdup.c \
		ft_memset.c	ft_calloc.c	ft_toupper.c ft_memmove.c \
		ft_tolower.c	ft_strchr.c	ft_strrchr.c ft_putnbr_fd.c	 ft_strncmp.c  ft_putchar_fd.c \
		ft_strnstr.c  ft_memcpy.c ft_memchr.c ft_memcmp.c ft_strjoin.c	ft_split.c	ft_strmapi.c ft_striteri.c  ft_putendl_fd.c  ft_strtrim.c	ft_putstr_fd.c	ft_itoa.c	ft_strjoin.c\

BONUSSRC = ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c ft_lstmap_bonus.c ft_lstiter_bonus.c \

OBJ = $(SRC:%.c=%.o)

OBJBONUS = $(BONUSSRC:%.c=%.o)

$(NAME) : $(OBJ)
		ar rc $(NAME) $(OBJ)

all : $(NAME) bonus

# %.o : %.c $(INC)													
# 		$(CC) -c $(CFLAGS) $< -o $@

bonus : $(OBJBONUS)
		ar rc $(NAME) $(OBJBONUS)

clean :
		@rm -rf $(OBJBONUS) $(OBJ)

fclean :
		@rm -f $(NAME) $(OBJBONUS) $(OBJ)

re : fclean all